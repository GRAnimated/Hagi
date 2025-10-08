#pragma once

#include "NerdCommonLibs/source/core/nerd_result.h"

namespace nerd::io {
class From;

class IFile {
public:
    enum From {
        FROM_START = 0,
        FROM_CURRENT = 1,
        FROM_END = 2,
    };

    virtual ~IFile();
    virtual bool IsOpen() const = 0;
    virtual int Close() = 0;
    virtual nerd::Result Read(void* buffer, unsigned long size, unsigned long* readSize) = 0;
    virtual nerd::Result ReadAtPos(void* buffer, unsigned long size, unsigned long pos,
                                   unsigned long* readSize);
    virtual nerd::Result Write(const void* buffer, unsigned long size, unsigned long* writtenSize) = 0;
    virtual nerd::Result WriteAtPos(const void* buffer, unsigned long size, unsigned long pos,
                                    unsigned long* writtenSize)
        = 0;
    virtual nerd::Result GetPos(unsigned long* pos) const = 0;
    virtual nerd::Result SetPos(long pos, From from, unsigned long* newPos) = 0;
    virtual nerd::Result GetSize(unsigned long* size) const = 0;
    virtual nerd::Result CheckEof() const;
    virtual nerd::Result Truncate() = 0;
    virtual nerd::Result Flush() = 0;
};
}  // namespace nerd::io
