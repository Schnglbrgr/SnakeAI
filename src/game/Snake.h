#pragma once

#include "Direction.h"
#include "Position.h"
#include <deque>


class Snake {
public:
    Snake(int startX, int startY);

    void Move();
    void ChangeDirection(Direction newDirection);
    void Grow();
    
    void Reset(int startX, int startY);
    
    bool OccupiesPosition(const Position& position) const;

    const std::deque<Position>& GetBody() const;
    Position GetHead() const;
    Direction GetDirection() const;

    bool HasSelfCollision() const;

private:
    std::deque<Position> body;
    Direction direction;
};
