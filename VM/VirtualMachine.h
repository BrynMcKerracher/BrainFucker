/**
 * @file VirtualMachine.h
 * @author brynm
 */
#ifndef BRAINFUCKER_VIRTUALMACHINE_H
#define BRAINFUCKER_VIRTUALMACHINE_H

#include <vector>
#include "../Bytecode/Op.h"

namespace BrainFucker::VM {
    class VirtualMachine {
    public:
        bool Execute(const std::vector<Bytecode::Op::Type>& opSequence);
    private:
        std::size_t pc = 0;
        std::vector<Bytecode::Op::Type> ops;
        uint8_t* memptr = memory;
        uint8_t memory[30000] = {};

        uint8_t ReadSingle();
        uint16_t ReadDouble();
    };
} // BrainFucker

#endif //BRAINFUCKER_VIRTUALMACHINE_H