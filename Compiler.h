/**
 * @file Compiler.h
 * @author brynm
 */
#ifndef BRAINFUCKER_COMPILER_H
#define BRAINFUCKER_COMPILER_H

#include <string>
#include <vector>

#include "Bytecode/Op.h"

namespace BrainFucker {
    class Compiler {
    public:
        std::vector<Bytecode::Op::Type> Compile(const std::string& source);
    };
} // BrainFucker

#endif //BRAINFUCKER_COMPILER_H