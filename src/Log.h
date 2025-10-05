#pragma once

namespace Log {
void Line(const char* msg, ...);
void Line2(const char* format, ...);
void Assert(const char* filePath, int lineNumber, const char* functionName, const char* format, ...);
void Assert(const char* functionName, const char* filePath, int lineNumber, const char* format, ...);
}  // namespace Log
