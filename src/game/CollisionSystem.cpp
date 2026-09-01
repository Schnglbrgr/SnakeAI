#pragma once

#include "CollisionSystem.h"


CollisionType CollisionSystem::Check(const Grid& grid, const Snake& snake, const Food& food) {
    Position head = snake.GetHead();

    if (head.x < 0 || head.x == grid.GetWidth() || head.y < 0 || head.y == grid.GetHeight())
        return CollisionType::Wall;

    if (snake.HasSelfCollision())
        return CollisionType::Self;

    if (head == food.GetPosition())
        return CollisionType::Food;

    return CollisionType::None;
}
