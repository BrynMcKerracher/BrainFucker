/**
 * @file PrinterVisitor.cpp
 * @author brynm
 */
#include "PrinterVisitor.h"

#include <iostream>

namespace BrainFucker::AST {
    void PrinterVisitor::Visit(const NodePtr& expr) {
        expr->Accept(this);
    }

    std::any PrinterVisitor::VisitAtomicOperation(AtomicOperation *expr) {
        std::cout << Token::TypeToString(expr->type) << " ";
        return 0;
    }

    std::any PrinterVisitor::VisitBlockScope(BlockScope *expr) {
        std::cout << "\n[ (" << expr->subNodes.size() << ") ";
        for (NodePtr& subExprs : expr->subNodes) {
            subExprs->Accept(this);
        }
        std::cout << "]\n";
        return 0;
    }

    std::any PrinterVisitor::VisitGlobalScope(GlobalScope *expr) {
        for (NodePtr& subExprs : expr->subNodes) {
            subExprs->Accept(this);
        }
        return 0;
    }

} // BrainFucker