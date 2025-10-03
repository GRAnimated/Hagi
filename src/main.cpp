#include "Program.h"
#include "hagi/Hagi.h"

#include <nn/oe.h>
#include <nn/os.h>

void* __dso_handle = 0;  // to fix an issue when using the STL, for some reason.

void sub_7100000710();

// NON_MATCHING
void Init(int argc, char** argv) {
    sub_7100000710();
    // TODO: magic numbers
    nn::oe::SetPerformanceConfiguration(nn::oe::PerformanceMode_Boost, 65537);
    nn::oe::SetPerformanceConfiguration(nn::oe::PerformanceMode_Normal, 131076);

    Hagi program = Hagi(argc, argv);
}

// NON_MATCHING: Init is incomplete so it inlines into nnMain
extern "C" void nnMain() {
    int argc = nn::os::GetHostArgc();
    char** argv = nn::os::GetHostArgv();
    Init(argc, argv);
}
