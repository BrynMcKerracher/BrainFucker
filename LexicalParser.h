/**
 * @file LexicalParser.h
 * @author brynm
 */
#ifndef BRAINFUCKER_LEXICALPARSER_H
#define BRAINFUCKER_LEXICALPARSER_H

#include "Scanner.h"
#include "AST/Node.h"
#include "AST/BlockScope.h"
#include "AST/GlobalScope.h"

namespace BrainFucker {
    class LexicalParser {
    public:
        AST::GlobalScopePtr Parse(const std::vector<Token>& tokens);
    private:
        std::size_t current = 0;
        std::vector<Token> tokenStream;
        AST::GlobalScopePtr globalScope;

        AST::NodePtr Expression();

        bool Match(std::initializer_list<Token::Type> types);
        [[nodiscard]] bool Check(Token::Type type) const;
        [[nodiscard]] bool AtEndOfStream() const;
        Token Advance();
        Token Consume(Token::Type type);
        [[nodiscard]] const Token& Peek() const;
        [[nodiscard]] const Token& Previous() const;
    };
} // BrainFucker

#endif //BRAINFUCKER_LEXICALPARSER_H