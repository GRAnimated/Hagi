#include "Debug.h"

namespace debug {
// NON_MATCHING
void println(const char* msg) {}

// NON_MATCHING
void println(const char* format, ...) {}

// NON_MATCHING
void assert(const char* filePath, int lineNumber, const char* functionName, const char* assertMsg,
            const char* line, ...) {}

// NON_MATCHING
void assert(const char* functionName, const char* filePath, int lineNumber, const char* assertMsg,
            const char* line, ...) {}

}  // namespace debug
