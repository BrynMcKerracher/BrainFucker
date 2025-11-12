/**
 * @file BlockExpression.cpp
 * @author brynm
 */
#include "BlockScope.h"
#include "Visitor.h"

namespace BrainFucker::AST {
    BlockScope::BlockScope() {
        nodeType = Block;
    }

    std::any BlockScope::Accept(Visitor* visitor) {
        return visitor->VisitBlockScope(this);
    }
} // BrainFucker