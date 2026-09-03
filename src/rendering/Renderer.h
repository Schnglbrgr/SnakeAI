#pragma once

#include "raylib.h"
#include "../game/Grid.h"
#include "../game/Snake.h"
#include "../game/Food.h"

class Renderer {
public:
    Renderer();
    ~Renderer();

    void LoadAssets();

    Color cellColor1 = {.r = 162, .g = 209, .b = 73, .a = 255};
    Color cellColor2 = {.r = 170, .g = 215, .b = 81, .a = 255};
    Color backgroundColor = {.r = 0, .g = 51, .b = 0, .a = 255};

    RenderTexture2D CreateGridTexture(const Grid& grid);

    void DrawGrid(const Grid& grid) const;
    void DrawSnake(const Snake& snake, const Grid& grid) const;
    void DrawFood(const Food& food, const Grid& grid) const;
    
    int GetPadding() const;

private:
    RenderTexture2D gridTexture{};
    
    Texture2D foodTexture{};
    Texture2D snakeBodyTexture{};
    Texture2D snakeHeadTexture{};
    
    int padding = 40;
};
