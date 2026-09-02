#pragma once

#include <cstdint>

#include "AIState.h"

using StateKey = uint16_t;

StateKey EncodeAIStateToKey(const AIState& state);