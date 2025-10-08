#pragma once

#include <cstdarg>

namespace nerd {

enum Result {
    RESULT_SUCCESS = 0,
    RESULT_END = 1,
    RESULT_UNKNOWN_ERROR = 0x80000003,
    RESULT_INVALID_PARAMETERS = 0x80000004,
    RESULT_NOT_SUPPORTED = 0x80000005,
    RESULT_TIMEOUT = 0x80000006,
    RESULT_NOT_ENOUGH_MEMORY = 0x80000007,
    RESULT_NOT_FOUND = 0x80000008,
    RESULT_BUSY = 0x80000009,
    RESULT_FORBIDDEN = 0x8000000A,
    RESULT_EXHAUSTED = 0x8000000B,
    RESULT_LOGIC_ERROR = 0x8000000C,
    RESULT_CORRUPT = 0x8000000D,
    RESULT_INSUFFICIENT_BUFFER = 0x8000000E,
    RESULT_NOT_IMPLEMENTED = 0x8000000F,
    RESULT_OVERFLOW = 0x80000010,
    RESULT_LOW_PERFORMANCE = 0x40000002,

    // nerd::io
    ResultAlreadyInitialized = 0x80010001,
    ResultNotInitialized = 0x80010002,
    ResultAccessDenied = 0x80010003,
    ResultInvalidDescriptor = 0x80010004,
    ResultNotFile = 0x80010007,
    ResultNotDirectory = 0x80010008,
    ResultIOError = 0x8001000A,
    ResultAIONotInitialized = 0x8001000B,
    ResultUnalignedBuffer = 0x8001000D,
    ResultInvalidAndroidPath = 0x8001000E,
    ResultAssetManagerNotInitialized = 0x8001000F,
    ResultInvalidAccess = 0x80010010,
    ResultInvalidMode = 0x80010011,
    ResultNoMoreEntry = 0x10005,
    ResultAlreadyExists = 0x10006,
    ResultAIOPending = 0x1000C
};

// TODO: Some of these don't exist in Hagi due to being unused
void GetResultName(unsigned int);
void FormatResultFailedMessage(char*, unsigned long, unsigned int, const char*, int, const char*,
                               std::va_list);
void SetResultFailedCallback(bool (*)(unsigned int, const char*, int, const char*, std::va_list));
void GetResultFailedCallback();
void OnResultFailed(unsigned int, const char*, int, const char*, ...);
}  // namespace nerd
