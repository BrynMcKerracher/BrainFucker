/**
 * @file VirtualMachine.cpp
 * @author brynm
 */
#include "VirtualMachine.h"

#include <iostream>

using namespace BrainFucker::Bytecode;

namespace BrainFucker::VM {
    bool VirtualMachine::Execute(const std::vector<Op::Type> &opSequence) {
        pc = 0;
        ops = opSequence;
        memptr = memory;

        uint64_t instructionsExecuted = 0;

        while (pc < ops.size()) {
            instructionsExecuted++;
            switch (ops[pc++]) {
                case Op::Nop: break;
                case Op::IncrementData: *memptr += 1; break;
                case Op::IncrementDataSingle: {
                    *memptr += ReadSingle();
                    break;
                }
                case Op::IncrementDataDouble: {
                    *memptr += ReadDouble();
                    break;
                }
                case Op::DecrementData: *memptr -= 1; break;
                case Op::DecrementDataSingle: {
                    *memptr -= ReadSingle();
                    break;
                }
                case Op::DecrementDataDouble: {
                    *memptr -= ReadDouble();
                    break;
                }
                case Op::IncrementPointer: memptr++; break;
                case Op::IncrementPointerSingle: {
                    memptr += ReadSingle();
                    break;
                }
                case Op::IncrementPointerDouble: {
                    memptr += ReadDouble();
                    break;
                }
                case Op::DecrementPointer: memptr--; break;
                case Op::DecrementPointerSingle: {
                    memptr -= ReadSingle();
                    break;
                }
                case Op::DecrementPointerDouble: {
                    memptr -= ReadDouble();
                    break;
                }
                case Op::Output: {
                    std::cout << *memptr;
                    break;
                }
                case Op::Input: {
                    std::cin >> *memptr;
                    break;
                }
                case Op::JumpIfFalse: {
                    const uint16_t addr = ReadDouble();
                    if (*memptr == 0) {
                        pc = addr;
                    }
                    break;
                }
                case Op::JumpIfTrue: {
                    const uint16_t addr = ReadDouble();
                    if (*memptr != 0) {
                        pc = addr;
                    }
                    break;
                }
                case Op::ZeroMem: {
                    *memptr = 0;
                    break;
                }
                case Op::AddCell: {
                    const uint16_t offset = ReadDouble();
                    *(memptr + offset) += *memptr;
                    *memptr = 0;
                    break;
                }
                case Op::SubCell: {
                    const uint16_t offset = ReadDouble();
                    *(memptr - offset) += *memptr;
                    *memptr = 0;
                    break;
                }
                default: return false;
            }
        }
        std::cout << "Executed: " << instructionsExecuted << "\n";
        return true;
    }

    uint8_t VirtualMachine::ReadSingle() {
        return ops[pc++];
    }

    uint16_t VirtualMachine::ReadDouble() {
        uint16_t value = 0;
        value |= ops[pc++] << 8;
        value |= ops[pc++];
        return value;
    }
} // BrainFucker