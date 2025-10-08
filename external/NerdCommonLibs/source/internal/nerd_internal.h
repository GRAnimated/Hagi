#pragma once

#include "NerdCommonLibs/source/core/nerd_result.h"
#include "vapours/results/results_common.hpp"

namespace nerd::internal {
nerd::Result NNResultToResult(nn::Result);
}
