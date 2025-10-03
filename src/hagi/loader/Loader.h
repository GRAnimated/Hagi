#pragma once

#include "dolphin/DolFileType.h"

class Loader {
public:
    // pDolFile->Initialize(pLoaderFileInterface, type)

    static dolphin::DolFileType GetFileType(const char* filename);
};
