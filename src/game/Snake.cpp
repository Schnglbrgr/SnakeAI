#include "Snake.h"


Snake::Snake(const int startX, const int startY) : direction(Direction::Right) {
    Reset(startX, startY);
}


void Snake::Reset(int startX, int startY) {
    body.clear();

    direction = Direction::Right;

    body.push_back({.x = startX, .y = startY});
    body.push_back({.x = startX - 1, .y = startY});
    body.push_back({.x = startX - 2, .y = startY});
}


void Snake::ChangeDirection(const Direction newDirection) {
    if (direction == Direction::Up && newDirection == Direction::Down)
        return;

    if (direction == Direction::Down && newDirection == Direction::Up)
        return;

    if (direction == Direction::Left && newDirection == Direction::Right)
        return;

    if (direction == Direction::Right && newDirection == Direction::Left)
        return;

    direction = newDirection;
}


bool Snake::OccupiesPosition(const Position& position) const {
    for (const Position& bodyPart : body) {
        if (bodyPart == position)
            return true;
    }

    return false;
}


void Snake::Grow() {
    body.push_back(body.back());
}


const std::deque<Position>& Snake::GetBody() const {
    return body;
}


Position Snake::GetHead() const {
    return body[0];
}


Direction Snake::GetDirection() const {
    return direction;
}


bool Snake::HasSelfCollision() const {
    const Position& head = body[0];

    for (size_t i = 1; i < body.size(); i++) {
        if (head == body[i])
            return true;
    }
    return false;
}


void Snake::Move() {
    Position delta{};

    switch (direction) {
    case Direction::Up:
        delta = {.x = 0, .y = -1};
        break;
    case Direction::Down:
        delta = {.x = 0, .y = 1};
        break;
    case Direction::Left:
        delta = {.x = -1, .y = 0};
        break;
    case Direction::Right:
        delta = {.x = 1, .y = 0};
        break;
    }
    Position newHead = body.front() + delta;
    body.push_front(newHead);
    body.pop_back();
}
