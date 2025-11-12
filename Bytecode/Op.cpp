/**
 * @file Op.cpp
 * @author brynm
 */
#include "Op.h"

namespace BrainFucker::Bytecode {
    std::string Op::ToString(const Type op) {
        switch (op) {
            case Op::Nop:                     return "NOP";
            case Op::IncrementData:           return "IND";
            case Op::IncrementDataSingle:     return "IDS";
            case Op::IncrementDataDouble:     return "IDD";
            case Op::DecrementData:           return "DED";
            case Op::DecrementDataSingle:     return "DDS";
            case Op::DecrementDataDouble:     return "DDD";
            case Op::IncrementPointer:        return "INP";
            case Op::IncrementPointerSingle:  return "IPS";
            case Op::IncrementPointerDouble:  return "IPD";
            case Op::DecrementPointer:        return "DEP";
            case Op::DecrementPointerSingle:  return "DPS";
            case Op::DecrementPointerDouble:  return "DPD";
            case Op::ZeroMem:                 return "ZEM";
            case Op::Output:                  return "OUT";
            case Op::Input:                   return "CIN";
            case Op::JumpIfFalse:             return "JIF";
            case Op::JumpIfTrue:              return "JIT";
            case Op::AddCell:                 return "ADD";
            default:                          return "-";
        }
    }

    std::size_t Op::NumArgs(const Type op) {
        switch (op) {
            case Op::Nop:                     return 0;
            case Op::IncrementData:           return 0;
            case Op::IncrementDataSingle:     return 1;
            case Op::IncrementDataDouble:     return 2;
            case Op::DecrementData:           return 0;
            case Op::DecrementDataSingle:     return 1;
            case Op::DecrementDataDouble:     return 2;
            case Op::IncrementPointer:        return 0;
            case Op::IncrementPointerSingle:  return 1;
            case Op::IncrementPointerDouble:  return 2;
            case Op::DecrementPointer:        return 0;
            case Op::DecrementPointerSingle:  return 1;
            case Op::DecrementPointerDouble:  return 2;
            case Op::ZeroMem:                 return 0;
            case Op::Output:                  return 0;
            case Op::Input:                   return 0;
            case Op::JumpIfFalse:             return 2;
            case Op::JumpIfTrue:              return 2;
            case Op::AddCell:                 return 1;
            default:                          return 0;
        }
    }
} // BrainFucker