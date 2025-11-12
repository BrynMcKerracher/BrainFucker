/**
 * @file SourceCleaner.h
 * @author brynm
 */
#ifndef BRAINFUCKER_SOURCECLEANER_H
#define BRAINFUCKER_SOURCECLEANER_H

#include <string>

namespace BrainFucker {
    struct SourceCleaner {
        static std::string Clean(const std::string& source);
    };
} // BrainFucker

#endif //BRAINFUCKER_SOURCECLEANER_H