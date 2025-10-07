#pragma once

namespace nerd::hagi {

class AiControl;
class Mmio;
class Pi;

// Audio Interface
class Ai {
public:
    Ai();
    ~Ai();
    bool Initialize(Mmio* mmio, Pi* pi, AiControl* aiControl);
    void InitializeRegisters();
    void Deinitialize(Mmio* mmio);

    static int ReadAiControlRegister(void* context);
    static int ReadAiVolumeRegister(void* context);
    static int ReadAiSampleRegister(void* context);
    static int ReadAiInterruptTimingRegister(void* context);
    static void WriteAiControlRegister(void* context, void*, int value);
    static void WriteAiVolumeRegister(void* context, void*, int value);
    static void WriteAiInterruptTimingRegister(void* context, void*, int value);

    AiControl* m_pAiControl = nullptr;
    Pi* m_pPi = nullptr;
    bool m_bIsInitialized = false;

    int m_iControlRegister;
    int m_iVolumeRegister;
    int m_iInterruptTimingRegister;
};

}  // namespace nerd::hagi
