/**
 * @file AtomicExpression.h
 * @author brynm
 */
#ifndef BRAINFUCKER_ATOMICEXPRESSION_H
#define BRAINFUCKER_ATOMICEXPRESSION_H

#include "Node.h"
#include "../Token.h"

namespace BrainFucker::AST {
    struct AtomicOperation final : Node {
        Token::Type type = Token::None;
        std::size_t data = 0;

        AtomicOperation();
        AtomicOperation(Token::Type type, std::size_t data);

        std::any Accept(Visitor *visitor) override;
    };

    typedef std::unique_ptr<AtomicOperation> AtomicOpPtr;
} // BrainFucker

#endif //BRAINFUCKER_ATOMICEXPRESSION_H