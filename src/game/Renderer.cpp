#include "Renderer.h"

Renderer::Renderer() {
}

Renderer::~Renderer() {
    UnloadTexture(foodTexture);
    UnloadRenderTexture(gridTexture);
}

void Renderer::LoadAssets() {
    foodTexture = LoadTexture("assets/apple.png");
}


RenderTexture2D Renderer::CreateGridTexture(const Grid& grid) {
    gridTexture = LoadRenderTexture(grid.GetWidth() * grid.GetCellSize(), grid.GetHeight() * grid.GetCellSize());

    BeginTextureMode(gridTexture);

    for (int x = 0; x < grid.GetWidth(); x++)
    {
        for (int y = 0; y < grid.GetHeight(); y++)
        {
            Color c = ((x + y) % 2 == 0) ? cellColor1 : cellColor2;

            DrawRectangle(x * grid.GetCellSize(), y * grid.GetCellSize(), grid.GetCellSize(), grid.GetCellSize(), c);
        }
    }

    EndTextureMode();
    return gridTexture;
}


void Renderer::DrawGrid() const {
    Rectangle source{0.0f, 0.0f, static_cast<float>(gridTexture.texture.width), -static_cast<float>(gridTexture.texture.height)};
    Vector2 position{0.0f, 0.0f};
    DrawTextureRec(gridTexture.texture, source, position, WHITE);
}


void Renderer::DrawSnake(const Snake& snake) {
}


void Renderer::DrawFood(const Food& food, const Grid& grid) {
    Vector2 pos = food.GetPosition();

    DrawTexture(foodTexture, pos.x * grid.GetCellSize(), pos.y * grid.GetCellSize(), WHITE);
}
