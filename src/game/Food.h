#pragma once

#include "raylib.h"

class Food
{
public:
    Food();

    Vector2 GetPosition() const;

    void SetPosition(int x, int y);

private:
    Vector2 position;
};
