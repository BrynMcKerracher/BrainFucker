/**
 * @file GlobalScope.h
 * @author brynm
 */
#ifndef BRAINFUCKER_GLOBALSCOPE_H
#define BRAINFUCKER_GLOBALSCOPE_H

#include <vector>
#include <memory>
#include "Node.h"

namespace BrainFucker::AST {
    struct GlobalScope final : Node {
        std::vector<NodePtr> subNodes;

        GlobalScope();

        std::any Accept(Visitor* visitor) override;
    };
    typedef std::unique_ptr<GlobalScope> GlobalScopePtr;
} // BrainFucker

#endif //BRAINFUCKER_GLOBALSCOPE_H