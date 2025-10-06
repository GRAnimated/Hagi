#pragma once

class Mmio {
public:
    void RegisterDeviceWriteCallback(int reg, void* context, void (*callback)(void*, void*, int));
    void RegisterGpuWriteCallback(int reg, void* context, void (*callback)(void*, void*, int));
    void RegisterDeviceReadCallback(int reg, void* context, int (*callback)(void*));
    void RegisterGpuReadCallback(int reg, void* context, int (*callback)(void*));
    void UnregisterDeviceWriteCallback(int reg);
    void UnregisterGpuWriteCallback(int reg);
    void UnregisterHostWriteCallback(int reg);
    void UnregisterDeviceReadCallback(int reg);
    void UnregisterGpuReadCallback(int reg);
    void UnregisterHostReadCallback(int reg);

    void* qword0;
    void* m_DeviceWriteCallbacks;
    void* m_GpuWriteCallbacks;
    void* m_HostWriteCallbacks;
    void* qword20;
    void* m_DeviceReadCallbacks;
    void* m_GpuReadCallbacks;
    void* m_HostReadCallbacks;
};
