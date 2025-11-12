/**
 * @file BlockExpression.h
 * @author brynm
 */
#ifndef BRAINFUCKER_BLOCKEXPRESSION_H
#define BRAINFUCKER_BLOCKEXPRESSION_H

#include <vector>
#include "Node.h"

namespace BrainFucker::AST {
    struct BlockScope final : Node {
        std::vector<NodePtr> subNodes;

        BlockScope();

        std::any Accept(Visitor* visitor) override;
    };

    typedef std::unique_ptr<BlockScope> BlockScopePtr;
} // BrainFucker

#endif //BRAINFUCKER_BLOCKEXPRESSION_H