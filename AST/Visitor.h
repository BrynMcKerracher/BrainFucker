/**
 * @file ASTVisitor.h
 * @author brynm
 */
#ifndef BRAINFUCKER_ASTVISITOR_H
#define BRAINFUCKER_ASTVISITOR_H

#include <any>
#include "AtomicOperation.h"
#include "BlockScope.h"
#include "GlobalScope.h"

namespace BrainFucker::AST {
    struct Visitor {
        virtual ~Visitor() = default;

        virtual std::any VisitAtomicOperation(AtomicOperation* expr) = 0;
        virtual std::any VisitBlockScope(BlockScope* expr) = 0;
        virtual std::any VisitGlobalScope(GlobalScope* expr) = 0;
    };
} // BrainFucker

#endif //BRAINFUCKER_ASTVISITOR_H