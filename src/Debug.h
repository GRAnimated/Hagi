#pragma once

namespace debug {
void println(const char* msg);
void println(const char* format, ...);
void assert(const char* filePath, int lineNumber, const char* functionName, const char* assertMsg,
            const char* line);
void assert(const char* functionName, const char* filePath, int lineNumber, const char* assertMsg,
            const char* line);
}  // namespace debug
