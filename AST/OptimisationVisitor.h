/**
 * @file OptimisationVisitor.h
 * @author brynm
 */
#ifndef BRAINFUCKER_OPTIMISATIONVISITOR_H
#define BRAINFUCKER_OPTIMISATIONVISITOR_H

#include "Visitor.h"

namespace BrainFucker::AST {
    class OptimisationVisitor final : Visitor {
    public:
        void Visit(Node* expr);
    private:
        std::any VisitAtomicOperation(AtomicOperation* expr) override;
        std::any VisitBlockScope(BlockScope* expr) override;
        std::any VisitGlobalScope(GlobalScope *expr) override;

        static std::size_t IsForwardAddExpression(BlockScope* expr);
        static bool MatchAtomicTypes(const std::vector<NodePtr>& subExprs, std::initializer_list<Token::Type> types);
    };
} // BrainFucker

#endif //BRAINFUCKER_OPTIMISATIONVISITOR_H