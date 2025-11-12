/**
 * @file BytecodeVisitor.cpp
 * @author brynm
 */
#include "BytecodeVisitor.h"
#include "../Bytecode/Op.h"

using namespace BrainFucker::Bytecode;

namespace BrainFucker::AST {
    std::vector<Op::Type> BytecodeVisitor::Visit(Node* expr) {
        ops.clear();
        expr->Accept(this);
        return ops;
    }

    std::any BytecodeVisitor::VisitAtomicOperation(AtomicOperation* expr) {
        switch (expr->type) {
            case Token::Type::AddData: WriteVariableInstruction(
                Op::IncrementData, Op::IncrementDataSingle,Op::IncrementDataDouble, expr->data
            ); break;
            case Token::Type::SubData: WriteVariableInstruction(
                Op::DecrementData, Op::DecrementDataSingle,Op::DecrementDataDouble, expr->data
            ); break;
            case Token::Type::AddMem: WriteVariableInstruction(
                Op::IncrementPointer, Op::IncrementPointerSingle,Op::IncrementPointerDouble, expr->data
            ); break;
            case Token::Type::SubMem: WriteVariableInstruction(
                Op::DecrementPointer, Op::DecrementPointerSingle,Op::DecrementPointerDouble, expr->data
            ); break;
            case Token::Type::Input:        ops.emplace_back(Op::Input); break;
            case Token::Type::Output:       ops.emplace_back(Op::Output); break;
            case Token::Type::ClearMem:     ops.emplace_back(Op::ZeroMem); break;
            case Token::Type::AddCell: {
                WriteOp(Op::Type::AddCell);
                WriteOp(static_cast<Op::Type>(expr->data >> 8));
                WriteOp(static_cast<Op::Type>(expr->data));
                break;
            }
            case Token::Type::SubCell: {
                WriteOp(Op::Type::SubCell);
                WriteOp(static_cast<Op::Type>(expr->data >> 8));
                WriteOp(static_cast<Op::Type>(expr->data));
                break;
            }
            default: return 0;
        }
        return 0;
    }

    std::any BytecodeVisitor::VisitBlockScope(BlockScope* expr) {
        WriteOp(Op::JumpIfFalse);
        const uint16_t patchIndex = ops.size();
        WriteOps({0});
        WriteOps({0});
        for (const NodePtr& expression : expr->subNodes) {
            expression->Accept(this);
        }
        WriteOp(Op::JumpIfTrue);
        WriteOp(static_cast<Op::Type>((patchIndex + 2) >> 8));
        WriteOp(static_cast<Op::Type>(patchIndex + 2));
        const uint16_t jitPatchIndex = ops.size();

        //Backpatch forward jump
        ops[patchIndex] = static_cast<Op::Type>(jitPatchIndex >> 8);
        ops[patchIndex + 1] = static_cast<Op::Type>(jitPatchIndex);
        return 0;
    }

    std::any BytecodeVisitor::VisitGlobalScope(GlobalScope* expr) {
        for (const NodePtr& expression : expr->subNodes) {
            expression->Accept(this);
        }
        return 0;
    }

    void BytecodeVisitor::WriteOps(const std::initializer_list<uint8_t> bytes) {
        for (uint8_t byte : bytes) {
            ops.emplace_back(static_cast<Op::Type>(byte));
        }
    }

    void BytecodeVisitor::WriteOp(Op::Type op) {
        ops.emplace_back(op);
    }

    void BytecodeVisitor::WriteVariableInstruction(const Op::Type immediate, const Op::Type single, const Op::Type wide, const std::size_t length) {
        if (length == 1) {
            WriteOp(immediate);
        }
        else if (length < 256) {
            WriteOp(single);
            WriteOps({static_cast<uint8_t>(length)});
        }
        else if (length < 65536) {
            WriteOp(wide);
            WriteOps({static_cast<uint8_t>(length >> 8)});
            WriteOps({static_cast<uint8_t>(length)});
        }
    }
} // BrainFucker