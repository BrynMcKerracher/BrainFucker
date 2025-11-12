/**
 * @file Token.cpp
 * @author brynm
 */
#include "Token.h"

namespace BrainFucker {
    std::string Token::TypeToString(const Type type) {
        switch (type) {
            case None:          return "None";
            case AddMem:        return "AddMem";
            case SubMem:        return "SubMem";
            case AddData:       return "AddData";
            case SubData:       return "SubData";
            case ClearMem:      return "ClearMem";
            case Input:         return "Input";
            case Output:        return "Output";
            case JumpForward:   return "JumpForward";
            case JumpBackward:    return "JumpBackward";
            case EndOfFile:     return "EOF";
            default:            return "Unknown";
        };
    }
} // BrainFucker