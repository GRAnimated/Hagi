#include "Log.h"

namespace Log {
void Line(const char* msg, ...) {}

void Line2(const char* format, ...) {}

// NON_MATCHING
void Assert(const char* filePath, int lineNumber, const char* functionName, const char* assertMsg,
            const char* line, ...) {}

// NON_MATCHING
void Assert(const char* functionName, const char* filePath, int lineNumber, const char* assertMsg,
            const char* line, ...) {}

}  // namespace Log
