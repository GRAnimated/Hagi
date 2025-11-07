#pragma once

namespace nerd::hanafuda {

class MemoryStreamReader {
public:
    MemoryStreamReader();
    virtual ~MemoryStreamReader();
    virtual void Read(void* destination, unsigned long a_iBufferSize);
    virtual long GetSize();
    virtual long GetPosition();

private:
    void* m_pBuffer;
    long m_iBufferSize;
    long m_iBufferPosition;
};

}  // namespace nerd::hanafuda
