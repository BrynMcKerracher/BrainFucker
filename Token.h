/**
 * @file Token.h
 * @author brynm
 */
#ifndef BRAINFUCKER_TOKEN_H
#define BRAINFUCKER_TOKEN_H

#include <string>

namespace BrainFucker {
    struct Token {
        enum Type {
            None,
            AddMem,
            SubMem,
            AddData,
            SubData,
            ClearMem,
            Input,
            Output,
            JumpForward,
            JumpBackward,
            AddCell,
            EndOfFile
        };

        Type type = None;
        std::size_t length = 0;

        static std::string TypeToString(Token::Type type);
    };
} // BrainFucker

#endif //BRAINFUCKER_TOKEN_H