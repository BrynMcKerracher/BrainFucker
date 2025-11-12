/**
 * @file LexicalParser.cpp
 * @author brynm
 */
#include "LexicalParser.h"

#include <algorithm>
#include <iostream>

#include "AST/AtomicOperation.h"
#include "AST/BlockScope.h"

namespace BrainFucker {
    AST::GlobalScopePtr LexicalParser::Parse(const std::vector<Token> &tokens) {
        tokenStream = tokens;
        globalScope = std::make_unique<AST::GlobalScope>();
        current = 0;

        while (!AtEndOfStream()) {
            globalScope->subNodes.emplace_back(Expression());
        }

        return std::move(globalScope);
    }

    AST::NodePtr LexicalParser::Expression() {
        if (Match({Token::Type::JumpForward})) {
            AST::BlockScopePtr blockExpr = std::make_unique<AST::BlockScope>();
            while (Peek().type != Token::Type::JumpBackward) {
                AST::NodePtr expr = Expression();

                if (AtEndOfStream()) {
                    std::cerr << "Parse Error: Unmatched '['\n";
                    throw std::exception();
                }

                blockExpr->subNodes.emplace_back(std::move(expr));
            }
            Consume(Token::Type::JumpBackward);
            return blockExpr;
        }
        Advance();
        return std::make_unique<AST::AtomicOperation>(Previous().type, Previous().length);
    }

    bool LexicalParser::Match(const std::initializer_list<Token::Type> types) {
        for (const Token::Type token : types) {
            if (Check(token)) {
                Advance();
                return true;
            }
        }
        return false;
    }

    bool LexicalParser::Check(const Token::Type type) const {
        if (AtEndOfStream()) return false;
        return Peek().type == type;
    }

    bool LexicalParser::AtEndOfStream() const {
        return Peek().type == Token::Type::EndOfFile;
    }

    Token LexicalParser::Advance() {
        if (!AtEndOfStream()) current++;
        return Previous();
    }

    Token LexicalParser::Consume(const Token::Type type) {
        if (Check(type)) return Advance();
        std::cerr << "Parse Error: Expected '" << Token::TypeToString(type) << "'\n";
        throw std::exception();
    }

    const Token& LexicalParser::Peek() const {
        return tokenStream[current];
    }

    const Token& LexicalParser::Previous() const {
        return tokenStream[current - 1];
    }
} // BrainFucker