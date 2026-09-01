#pragma once

#include <deque>

#include "Position.h"
#include "Direction.h"


struct GameState {
    std::deque<Position> snakeBody;
    Position foodPosition;

    int gridWidth;
    int gridHeight;

    Direction direction;

    bool gameOver;
};
