/**
 * @file Expression.h
 * @author brynm
 */
#ifndef BRAINFUCKER_EXPRESSION_H
#define BRAINFUCKER_EXPRESSION_H

#include <memory>
#include <any>

namespace BrainFucker::AST {
    struct Node {
        enum Type {
            Atomic,
            Block,
            Global
        };

        Type nodeType;

        virtual ~Node() = default;

        virtual std::any Accept(class Visitor* visitor) = 0;
    };

    typedef std::unique_ptr<Node> NodePtr;
} // BrainFucker

#endif //BRAINFUCKER_EXPRESSION_H