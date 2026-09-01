#pragma once

#include "CollisionType.h"
#include "Grid.h"
#include "Snake.h"
#include "Food.h"


class CollisionSystem {
public:
    static CollisionType Check(const Grid& grid, const Snake& snake, const Food& food);
};


