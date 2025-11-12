/**
 * @file Scanner.h
 * @author brynm
 */
#ifndef BRAINFUCKER_SCANNER_H
#define BRAINFUCKER_SCANNER_H

#include <vector>
#include <string>
#include "Token.h"

namespace BrainFucker {
    class Scanner {
    public:
        [[nodiscard]] std::vector<Token> Scan(const std::string& source);
    private:
        std::size_t current = 0;
        std::size_t start = 0;
        std::string sourceCode;
        std::vector<Token> tokens;

        [[nodiscard]] Token MakeConsecutiveToken(Token::Type type, char c);
        [[nodiscard]] Token MakeOpenControlFlowToken();
        [[nodiscard]] bool AtEndOfSource() const;
        [[nodiscard]] bool Match(char expected);
        [[nodiscard]] bool Match(char a, char b);
    };
} // BrainFucker

#endif //BRAINFUCKER_SCANNER_H