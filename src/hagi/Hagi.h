#pragma once

#include "Program.h"

class Hagi : public Program {
public:
    Hagi(int argc, char** argv);

    void sub_710016C0F0() override;
    void sub_710016C110() override;
    void nullsub_193() override;
    void Initialize() override;
};
