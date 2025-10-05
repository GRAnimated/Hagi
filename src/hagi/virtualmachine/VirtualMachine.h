#pragma once

class Config;
class HagiApplication;

class VirtualMachine {
public:
    VirtualMachine(HagiApplication* hagi);
    bool Initialize(Config* config);
};
