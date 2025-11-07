#include "HanafudaCommon/source/hanafuda_stream_reader.h"
#include <cstring>

namespace nerd::hanafuda {

MemoryStreamReader::MemoryStreamReader() {
    m_pBuffer = nullptr;
}

MemoryStreamReader::~MemoryStreamReader() = default;

void MemoryStreamReader::Read(void* destination, unsigned long a_iBufferSize) {
    memcpy(destination, static_cast<char*>(m_pBuffer) + m_iBufferPosition, a_iBufferSize);
    m_iBufferPosition += a_iBufferSize;
}

long MemoryStreamReader::GetSize() {
    return m_iBufferSize;
}

long MemoryStreamReader::GetPosition() {
    return m_iBufferPosition;
}

}  // namespace nerd::hanafuda
