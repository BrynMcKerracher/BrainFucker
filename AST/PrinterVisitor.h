/**
 * @file PrinterVisitor.h
 * @author brynm
 */
#ifndef BRAINFUCKER_PRINTERVISITOR_H
#define BRAINFUCKER_PRINTERVISITOR_H

#include "Visitor.h"

namespace BrainFucker::AST {
    class PrinterVisitor final : Visitor {
    public:
        void Visit(const NodePtr& expr);
    private:
        std::any VisitAtomicOperation(AtomicOperation* expr) override;
        std::any VisitBlockScope(BlockScope* expr) override;
        std::any VisitGlobalScope(GlobalScope *expr) override;
    };
} // BrainFucker

#endif //BRAINFUCKER_PRINTERVISITOR_H