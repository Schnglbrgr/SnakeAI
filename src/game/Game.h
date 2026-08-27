#pragma once

#include "Renderer.h"

class Game
{
public:
    Game();

    void Run();

private:
    
    Renderer renderer;
    Grid grid;
    Snake snake;
    Food food;
    
    void Render(const Food& food, const Grid& grid);
    void SpawnFood();
    
};
