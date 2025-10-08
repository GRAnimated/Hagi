#include "NerdCommonLibs/source/core/nerd_io_file.h"

#include "NerdCommonLibs/source/core/nerd_io.h"
#include "NerdCommonLibs/source/core/nerd_result.h"
#include "NerdCommonLibs/source/internal/nerd_internal.h"

#include <cstring>

namespace nerd::io {
File::File() {}

// NON_MATCHING: For some reason, because Sloop shows that this just calls Close(), which is matching.
File::~File() {
    Close();
}

bool File::IsOpen() const {
    return m_bIsOpen;
}

// NON_MATCHING: needs cleanup
nerd::Result nerd::io::File::Open(const char* path, Access access, Mode mode) {
    nerd::Result result = nerd::RESULT_INVALID_PARAMETERS;

    if (m_bIsOpen) {
        return nerd::RESULT_BUSY;
    }

    if (strchr(path, ':')) {
        nn::Result fileResult;

        switch (mode) {
        case MODE_CREATE:
            nerd::io::DeleteFile(path);

            fileResult = nn::fs::CreateFile(path, 0);
            if (fileResult.IsFailure()) {
                break;
            }

            m_Result = fileResult;
            return nerd::internal::NNResultToResult(fileResult);

        case MODE_TRUNCATE:
            result = nerd::io::DeleteFile(path);
            if ((result >> 30) != 0) {
                return result;
            }

        case MODE_NEW:
            fileResult = nn::fs::CreateFile(path, 0);
            if (fileResult.IsFailure()) {
                break;
            }

            m_Result = fileResult;
            return nerd::internal::NNResultToResult(fileResult);

        case MODE_OPEN:
        default:
            break;
        }

        unsigned int openFlags = (access & 2) ? ((access & 1) | 6) : (access & 1);

        fileResult = nn::fs::OpenFile(&m_FileHandle, path, openFlags);
        m_Result = fileResult;
        if (fileResult.IsSuccess()) {
            m_lPos = 0;
            if (mode == MODE_NEW) {
                long fileSize = 0;
                nn::Result res = nn::fs::GetFileSize(&fileSize, m_FileHandle);
                m_Result = res;
                if (fileSize != 0) {
                    return nerd::internal::NNResultToResult(res);
                }
                m_lPos = fileSize;
            }

            m_iAccess = access;
            m_bIsOpen = true;
            return nerd::RESULT_SUCCESS;
        }

        return nerd::internal::NNResultToResult(fileResult);
    }

    return result;
}

int File::Close() {
    if (m_bIsOpen) {
        if (m_iAccess & ACCESS_WRITE) {
            nn::fs::FlushFile(m_FileHandle);
        }

        nn::fs::CloseFile(m_FileHandle);
        m_bIsOpen = false;
        return 0;
    }

    return 0;
}

nerd::Result File::Read(void* buffer, unsigned long size, unsigned long* readSize) {
    *readSize = 0;

    if (!size)
        return RESULT_SUCCESS;

    if (!m_bIsOpen)
        return ResultInvalidDescriptor;

    long fileSize;
    nn::Result res = nn::fs::GetFileSize(&fileSize, m_FileHandle);
    m_Result = res;

    if (res.IsFailure())
        return internal::NNResultToResult(res);

    if (m_lPos <= fileSize) {
        res = nn::fs::ReadFile(readSize, m_FileHandle, m_lPos, buffer, size);

        m_Result = res;
        if (res.IsFailure())
            return internal::NNResultToResult(res);
        m_lPos += *readSize;
        return (Result)res.GetInnerValueForDebug();
    }

    return RESULT_SUCCESS;
}

nerd::Result File::ReadAtPos(void* buffer, unsigned long size, unsigned long pos, unsigned long* readSize) {
    *readSize = 0;

    if (size != 0)
        return IFile::ReadAtPos(buffer, size, pos, readSize);

    return RESULT_SUCCESS;
}

nerd::Result File::Write(const void* buffer, unsigned long size, unsigned long* writtenSize) {
    *writtenSize = 0;
    if (!size)
        return RESULT_SUCCESS;

    if (!m_bIsOpen)
        return ResultInvalidDescriptor;

    nn::Result res = nn::fs::WriteFile(m_FileHandle, m_lPos, buffer, size, {});
    m_Result = res;
    if (res.IsFailure())
        return internal::NNResultToResult(res);

    m_lPos += size;
    *writtenSize = size;
    return (Result)res.GetInnerValueForDebug();
}

nerd::Result File::WriteAtPos(const void* buffer, unsigned long size, unsigned long pos,
                              unsigned long* writtenSize) {
    *writtenSize = 0;

    if (size != 0)
        return IFile::WriteAtPos(buffer, size, pos, writtenSize);

    return RESULT_SUCCESS;
}

nerd::Result File::GetPos(unsigned long* pos) const {
    if (!m_bIsOpen)
        return ResultInvalidDescriptor;

    *pos = m_lPos;
    return RESULT_SUCCESS;
}

// NON_MATCHING: one of the from cases is wrong
nerd::Result File::SetPos(long pos, From from, unsigned long* newPos) {
    long target = 0;

    if (newPos)
        *newPos = 0;

    if (!m_bIsOpen)
        return ResultInvalidDescriptor;

    unsigned long fileSize = 0;
    if (from == IFile::From::FROM_START) {
        target = 0;

    } else if (from == IFile::From::FROM_CURRENT) {
        target = m_lPos;

    } else if (from == IFile::From::FROM_END) {
        nerd::Result res = nerd::io::File::GetSize(&fileSize);
        if (res >> 30)
            return res;
        target = fileSize + pos;
    }

    target += pos;

    if (target < 0)
        return RESULT_INVALID_PARAMETERS;

    m_lPos = target;
    if (newPos)
        *newPos = target;

    return RESULT_SUCCESS;
}

nerd::Result File::GetSize(unsigned long* size) const {
    if (!m_bIsOpen)
        return ResultInvalidDescriptor;

    long fileSize;
    nn::Result res = nn::fs::GetFileSize(&fileSize, m_FileHandle);
    if (res.IsFailure())
        return internal::NNResultToResult(res);

    // TODO: nn::Result doesn't let you change the result, but it needs to be set to 0 here
    *(int*)&m_Result = 0;
    *size = fileSize;

    return RESULT_SUCCESS;
}

nerd::Result File::Truncate() {
    if (!m_bIsOpen)
        return ResultInvalidDescriptor;

    unsigned long pos;
    nerd::Result result = GetPos(&pos);
    if (result >> 30)
        return result;

    nn::Result nnResult = nn::fs::SetFileSize(m_FileHandle, pos);
    m_Result = nnResult;
    if (nnResult.IsFailure())
        return nerd::internal::NNResultToResult(nnResult);

    return RESULT_SUCCESS;
}

nerd::Result File::Flush() {
    if (!m_bIsOpen)
        return ResultInvalidDescriptor;

    nn::Result result = nn::fs::FlushFile(m_FileHandle);
    if (result.IsFailure())
        return nerd::internal::NNResultToResult(result);

    return RESULT_SUCCESS;
}

}  // namespace nerd::io
