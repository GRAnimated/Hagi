#pragma once

namespace debug {
void println(const char* msg);
void println(const char* format, ...);
void assert(const char* filePath, int lineNumber, const char* functionName, const char* format, ...);
void assert(const char* functionName, const char* filePath, int lineNumber, const char* format, ...);
}  // namespace debug
