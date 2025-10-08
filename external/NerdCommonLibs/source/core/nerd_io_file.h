#pragma once

#include "NerdCommonLibs/source/core/nerd_io_ifile.h"
#include "nn/fs.h"

namespace nerd::io {

class File : public IFile {
public:
    enum Access {
        ACCESS_READ = 1,
        ACCESS_WRITE = 2,
        ACCESS_READ_WRITE = ACCESS_READ | ACCESS_WRITE,
    };

    enum Mode {
        MODE_CREATE = 0,
        MODE_OPEN = 1,
        MODE_TRUNCATE = 2,
        MODE_NEW = 3,
    };

    File();

    ~File() override;
    bool IsOpen() const override;
    nerd::Result Open(const char* path, Access access, Mode mode);
    int Close() override;
    nerd::Result Read(void* buffer, unsigned long size, unsigned long* readSize) override;
    nerd::Result ReadAtPos(void* buffer, unsigned long size, unsigned long pos,
                           unsigned long* readSize) override;
    nerd::Result Write(const void* buffer, unsigned long size, unsigned long* writtenSize) override;
    nerd::Result WriteAtPos(const void* buffer, unsigned long size, unsigned long pos,
                            unsigned long* writtenSize) override;
    nerd::Result GetPos(unsigned long* pos) const override;
    nerd::Result SetPos(long pos, From from, unsigned long* newPos) override;
    nerd::Result GetSize(unsigned long* size) const override;
    nerd::Result Truncate() override;
    nerd::Result Flush() override;

    nn::fs::FileHandle m_FileHandle;
    nn::Result m_Result;
    bool m_bIsOpen = false;
    int m_iAccess;
    int m_iMode;
    long m_lPos = 0;
};
}  // namespace nerd::io
