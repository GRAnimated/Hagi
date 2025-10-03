#pragma once

#include "hagi/gekko/Gekko.h"
#include "hagi/virtualmachine/CpuSyncer.h"

class EventScheduler {
public:
    bool Initialize(Gekko*, const CpuSyncer&);
};
