#pragma once

#include <functional>


struct Position {
    int x;
    int y;


    bool operator==(const Position& other) const {
        return x == other.x && y == other.y;
    }


    bool operator!=(const Position& other) const {
        return !(*this == other);
    }


    Position operator+(const Position& other) const {
        return {x + other.x, y + other.y};
    }
};


struct PositionHash {
    std::size_t operator()(const Position& position) const {
        return std::hash<int>{}(position.x) ^ (std::hash<int>{}(position.y) << 1);
    }
};
