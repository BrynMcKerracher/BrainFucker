/**
 * @file OptimisationVisitor.cpp
 * @author brynm
 */
#include "OptimisationVisitor.h"

#include <iostream>

namespace BrainFucker::AST {
    void OptimisationVisitor::Visit(Node *expr) {
        expr->Accept(this);
    }

    std::any OptimisationVisitor::VisitAtomicOperation(AtomicOperation* expr) {
        return 0;
    }

    std::any OptimisationVisitor::VisitBlockScope(BlockScope* expr) {
        for (NodePtr& expression : expr->subNodes) {
            ApplyForwardAddOptimisation(expression);
            ApplyBackwardAddOptimisation(expression);
        }
        for (const NodePtr& expression : expr->subNodes) {
            expression->Accept(this);
        }
        return 0;
    }

    std::any OptimisationVisitor::VisitGlobalScope(GlobalScope *expr) {
        for (const NodePtr& expression : expr->subNodes) {
            expression->Accept(this);
        }
        return 0;
    }

    void OptimisationVisitor::ApplyBackwardAddOptimisation(NodePtr &expression) {
        if (expression->nodeType == Node::Block) {
            const std::size_t subSize = IsBackwardAddExpression(dynamic_cast<BlockScope*>(expression.get()));
            if (subSize > 0) {
                expression = std::make_unique<AtomicOperation>(Token::Type::SubCell, subSize);
            }
        }
    }

    void OptimisationVisitor::ApplyForwardAddOptimisation(NodePtr &expression) {
        if (expression->nodeType == Node::Block) {
            const std::size_t addSize = IsForwardAddExpression(dynamic_cast<BlockScope*>(expression.get()));
            if (addSize > 0) {
                expression = std::make_unique<AtomicOperation>(Token::Type::AddCell, addSize);
            }
        }
    }

    std::size_t OptimisationVisitor::IsForwardAddExpression(BlockScope* expr) {
        if (expr->subNodes.size() != 4) return 0;
        if (!MatchAtomicTypes(expr->subNodes,{
            Token::Type::SubData,
            Token::Type::AddMem,
            Token::Type::AddData,
            Token::Type::SubMem
        })) return 0;
        const AtomicOperation* subData = dynamic_cast<AtomicOperation*>(expr->subNodes[0].get());
        const AtomicOperation* addMem = dynamic_cast<AtomicOperation*>(expr->subNodes[1].get());
        const AtomicOperation* addData = dynamic_cast<AtomicOperation*>(expr->subNodes[2].get());
        const AtomicOperation* subMem = dynamic_cast<AtomicOperation*>(expr->subNodes[3].get());
        if (addMem->data != subMem->data or subData->data != 1 or addData->data != 1) return 0;
        return addMem->data;
    }

    std::size_t OptimisationVisitor::IsBackwardAddExpression(BlockScope* expr) {
        if (expr->subNodes.size() != 4) return 0;
        if (!MatchAtomicTypes(expr->subNodes,{
            Token::Type::SubData,
            Token::Type::SubMem,
            Token::Type::AddData,
            Token::Type::AddMem
        })) return 0;
        const AtomicOperation* subData = dynamic_cast<AtomicOperation*>(expr->subNodes[0].get());
        const AtomicOperation* subMem = dynamic_cast<AtomicOperation*>(expr->subNodes[1].get());
        const AtomicOperation* addData = dynamic_cast<AtomicOperation*>(expr->subNodes[2].get());
        const AtomicOperation* addMem = dynamic_cast<AtomicOperation*>(expr->subNodes[3].get());
        if (addMem->data != subMem->data or subData->data != 1 or addData->data != 1) return 0;
        return addMem->data;
    }


    bool OptimisationVisitor::MatchAtomicTypes(const std::vector<NodePtr> &subExprs, const std::initializer_list<Token::Type> types) {
        std::size_t i = 0;
        for (const Token::Type type : types) {
            const AtomicOperation* atomic = dynamic_cast<AtomicOperation*>(subExprs[i].get());
            if (!atomic or atomic->type != type) return false;
            ++i;
        }
        return true;
    }
} // BrainFucker