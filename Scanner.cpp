/**
 * @file Tokeniser.cpp
 * @author brynm
 */
#include "Scanner.h"

namespace BrainFucker {
    std::vector<Token> Scanner::Scan(const std::string &source) {
        start = current = 0;
        sourceCode = source;
        tokens.clear();

        while (!AtEndOfSource()) {
            start = current;
            switch (sourceCode[current++]) {
                case '>': tokens.emplace_back(MakeConsecutiveToken(Token::Type::AddMem, '>')); break;
                case '<': tokens.emplace_back(MakeConsecutiveToken(Token::Type::SubMem, '<')); break;
                case '+': tokens.emplace_back(MakeConsecutiveToken(Token::Type::AddData, '+')); break;
                case '-': tokens.emplace_back(MakeConsecutiveToken(Token::Type::SubData, '-')); break;
                case '.': tokens.emplace_back(Token {Token::Output, 1}); break;
                case ',': tokens.emplace_back(Token {Token::Input, 1}); break;
                case '[': tokens.emplace_back(MakeOpenControlFlowToken()); break;
                case ']': tokens.emplace_back(Token {Token::JumpBackward, 1}); break;
                default: break;
            }
        }
        tokens.emplace_back(Token {Token::Type::EndOfFile, 0});
        return tokens;
    }

    Token Scanner::MakeConsecutiveToken(const Token::Type type, const char c) {
        while (Match(c)) {}
        return {type, current - start};
    }

    Token Scanner::MakeOpenControlFlowToken() {
        if (Match('+', ']') or Match('-', ']')) {
            return {Token::Type::ClearMem, 1};
        }
        return {Token::Type::JumpForward, current - start};
    }

    bool Scanner::AtEndOfSource() const {
        return current >= sourceCode.size();
    }

    bool Scanner::Match(const char expected) {
        if (AtEndOfSource()) return false;
        if (sourceCode[current] != expected) return false;

        current++;
        return true;
    }

    bool Scanner::Match(const char a, const char b) {
        if (current + 1 >= sourceCode.size()) return false;
        if (sourceCode[current] != a or sourceCode[current + 1] != b) return false;

        current += 2;
        return true;
    }

} // BrainFucker