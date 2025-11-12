/**
 * @file AtomicExpression.cpp
 * @author brynm
 */
#include "AtomicOperation.h"

#include "Visitor.h"

namespace BrainFucker::AST {
    AtomicOperation::AtomicOperation() {
        nodeType = Atomic;
    }

    AtomicOperation::AtomicOperation(const Token::Type type, const std::size_t data) {
        nodeType = Atomic;
        this->type = type;
        this->data = data;
    }

    std::any AtomicOperation::Accept(Visitor *visitor) {
        return visitor->VisitAtomicOperation(this);
    }
} // BrainFucker