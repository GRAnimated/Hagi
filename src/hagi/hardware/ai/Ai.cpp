#include "hagi/hardware/ai/Ai.h"

#include "MxicCodeUtils/mxic/interfaces/Mmio.h"
#include "hagi/hardware/ai/AiControl.h"

namespace nerd::hagi {

Ai::Ai() {}

Ai::~Ai() {}

bool Ai::Initialize(Mmio* mmio, Pi* pi, AiControl* aiControl) {
    mmio->RegisterDeviceReadCallback(0x6C00, this, ReadAiControlRegister);
    mmio->RegisterDeviceReadCallback(0x6C04, this, ReadAiVolumeRegister);
    mmio->RegisterDeviceReadCallback(0x6C08, this, ReadAiSampleRegister);
    mmio->RegisterDeviceReadCallback(0x6C0C, this, ReadAiInterruptTimingRegister);
    mmio->RegisterDeviceWriteCallback(0x6C00, this, WriteAiControlRegister);
    mmio->RegisterDeviceWriteCallback(0x6C04, this, WriteAiVolumeRegister);
    mmio->RegisterDeviceWriteCallback(0x6C0C, this, WriteAiInterruptTimingRegister);
    m_pAiControl = aiControl;
    m_pPi = pi;
    m_bIsInitialized = true;
    return true;
}

void Ai::InitializeRegisters() {
    m_iControlRegister = 0;
    m_iVolumeRegister = 0;
    m_iInterruptTimingRegister = 0;
}

void Ai::Deinitialize(Mmio* mmio) {
    if (!m_bIsInitialized)
        return;

    mmio->UnregisterDeviceReadCallback(0x6C00);
    mmio->UnregisterDeviceReadCallback(0x6C04);
    mmio->UnregisterDeviceReadCallback(0x6C08);
    mmio->UnregisterDeviceReadCallback(0x6C0C);
    mmio->UnregisterDeviceWriteCallback(0x6C00);
    mmio->UnregisterDeviceWriteCallback(0x6C04);
    mmio->UnregisterDeviceWriteCallback(0x6C0C);
    m_bIsInitialized = false;
    m_pAiControl = nullptr;
    m_pPi = nullptr;
}

int Ai::ReadAiControlRegister(void* context) {
    return ((Ai*)context)->m_iControlRegister;
}

int Ai::ReadAiVolumeRegister(void* context) {
    return ((Ai*)context)->m_iVolumeRegister;
}

int Ai::ReadAiSampleRegister(void* context) {
    return ((Ai*)context)->m_pAiControl->_7100054300();
}

int Ai::ReadAiInterruptTimingRegister(void* context) {
    return ((Ai*)context)->m_iInterruptTimingRegister;
}

}  // namespace nerd::hagi
