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

    Color cellColor1 = {162, 209, 73, 255};
    Color cellColor2 = {170, 215, 81, 255};

    RenderTexture2D CreateGridTexture(const Grid& grid);

    void DrawGrid() const;
    void DrawSnake(const Snake& snake, const Grid& grid);
    void DrawFood(const Food& food, const Grid& grid);

private:
    RenderTexture2D gridTexture{};
    
    Texture2D foodTexture{};
    Texture2D snakeBodyTexture{};
    Texture2D snakeHeadTexture{};
};
