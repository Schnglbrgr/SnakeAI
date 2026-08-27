#pragma once

#include "raylib.h"
#include "Grid.h"
#include "Snake.h"
#include "Food.h"

class Renderer
{
public:
    Renderer();
    ~Renderer();
    
    void LoadAssets();

    Color cellColor1 = {162, 209, 73, 255};
    Color cellColor2 = {170, 215, 81, 255};
    
    RenderTexture2D CreateGridTexture(const Grid& grid);

    void DrawGrid() const;
    void DrawSnake(const Snake& snake);
    void DrawFood(const Food& food, const Grid& grid);
    
private:
    RenderTexture2D gridTexture;
    Texture2D foodTexture;
};
