#pragma once

#include "GameState.h"


struct StepResult {
    GameState state;
    float reward;
    bool done;
};
