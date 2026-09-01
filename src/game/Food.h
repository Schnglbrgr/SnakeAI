#pragma once

#include "Position.h"

class Food
{
public:
    Food();

    Position GetPosition() const;

    void SetPosition(int x, int y);

private:
    Position position;
};
