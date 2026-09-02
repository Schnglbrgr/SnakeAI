#pragma once

#include "../game/Direction.h"


struct AIState {
    bool dangerUp;
    bool dangerDown;
    bool dangerLeft;
    bool dangerRight;

    bool foodUp;
    bool foodDown;
    bool foodLeft;
    bool foodRight;

    Direction direction;
};
