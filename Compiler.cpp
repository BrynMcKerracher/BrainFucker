/**
 * @file Compiler.cpp
 * @author Bryn McKerracher
 */

#include "Compiler.h"
#include "Scanner.h"

#include <vector>
#include <iostream>

#include "LexicalParser.h"
#include "SourceCleaner.h"
#include "AST/BytecodeVisitor.h"
#include "AST/OptimisationVisitor.h"
#include "AST/PrinterVisitor.h"

namespace BrainFucker {
    std::vector<Bytecode::Op::Type> Compiler::Compile(const std::string &source) {
        Scanner scanner;
        const std::vector<Token> tokens = scanner.Scan(SourceCleaner::Clean(source));

        LexicalParser lexer;
        AST::NodePtr AST = lexer.Parse(tokens);

        //AST::PrinterVisitor printer;
        //printer.Visit(AST);

        AST::OptimisationVisitor optimisationVisitor;
        optimisationVisitor.Visit(AST.get());

        AST::BytecodeVisitor bytecodeVisitor;
        std::vector<Bytecode::Op::Type> ops = bytecodeVisitor.Visit(AST.get());

        /*
        for (std::size_t i = 0; i < ops.size(); ++i) {
            std::cout << i << ":\t" << Bytecode::Op::ToString(ops[i]);
            for (std::size_t k = 0; k < Bytecode::Op::NumArgs(ops[i]); ++k) {
                const uint64_t arg = ops[i + k + 1];
                std::cout << " " << arg;
            }
            std::cout << "\n";
            i += Bytecode::Op::NumArgs(ops[i]);
        }
        std::cout << ops.size() << "\n";
        */

        return ops;
    }
} // BrainFucker