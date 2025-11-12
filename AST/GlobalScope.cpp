/**
 * @file GlobalScope.cpp
 * @author brynm
 */
#include "GlobalScope.h"

#include "Visitor.h"

namespace BrainFucker::AST {
    GlobalScope::GlobalScope() {
        nodeType = Global;
    }

    std::any GlobalScope::Accept(Visitor* visitor) {
        return visitor->VisitGlobalScope(this);
    }
} // BrainFucker