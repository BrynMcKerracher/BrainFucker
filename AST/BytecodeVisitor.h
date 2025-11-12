/**
 * @file BytecodeVisitor.h
 * @author brynm
 */
#ifndef BRAINFUCKER_BYTECODEVISITOR_H
#define BRAINFUCKER_BYTECODEVISITOR_H

#include <any>
#include "Visitor.h"
#include "../Bytecode/Op.h"

namespace BrainFucker::AST {
    class BytecodeVisitor final : Visitor {
    public:
        std::vector<Bytecode::Op::Type> Visit(Node* expr);
    private:
        std::vector<Bytecode::Op::Type> ops;

        std::any VisitAtomicOperation(AtomicOperation* expr) override;
        std::any VisitBlockScope(BlockScope* expr) override;
        std::any VisitGlobalScope(GlobalScope* expr) override;

        void WriteOps(std::initializer_list<uint8_t> bytes);
        void WriteOp(Bytecode::Op::Type op);
        void WriteVariableInstruction(Bytecode::Op::Type immediate, Bytecode::Op::Type single, Bytecode::Op::Type wide, std::size_t length);
    };
} // BrainFucker

#endif //BRAINFUCKER_BYTECODEVISITOR_H