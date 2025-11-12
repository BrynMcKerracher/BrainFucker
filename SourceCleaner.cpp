/**
 * @file SourceCleaner.cpp
 * @author brynm
 */
#include "SourceCleaner.h"

namespace BrainFucker {
    std::string SourceCleaner::Clean(const std::string &source) {
        std::string cleaned;
        for (const char c : source) {
            switch (c) {
                case '>':
                case '<':
                case '+':
                case '-':
                case '.':
                case ',':
                case '[':
                case ']':
                    cleaned += c;
                    break;
                default: break;
            }
        }
        return cleaned;
    }

} // BrainFucker