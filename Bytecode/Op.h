/**
 * @file Op.h
 * @author brynm
 */
#ifndef BRAINFUCKER_OP_H
#define BRAINFUCKER_OP_H

#include <cstdint>
#include <string>

namespace BrainFucker::Bytecode {
    struct Op {
        enum Type : std::uint8_t {
            Nop,
            IncrementData,
            IncrementDataSingle,
            IncrementDataDouble,
            DecrementData,
            DecrementDataSingle,
            DecrementDataDouble,
            IncrementPointer,
            IncrementPointerSingle,
            IncrementPointerDouble,
            DecrementPointer,
            DecrementPointerSingle,
            DecrementPointerDouble,
            Output,
            Input,
            JumpIfFalse,
            JumpIfTrue,
            ZeroMem,
            AddCell
        };

        static std::string ToString(Type op);
        static std::size_t NumArgs(Type op);
    };
} // BrainFucker

#endif //BRAINFUCKER_OP_H