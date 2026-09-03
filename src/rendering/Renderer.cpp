#include "Renderer.h"


Renderer::Renderer() = default;


Renderer::~Renderer() {
    UnloadTexture(foodTexture);
    UnloadTexture(snakeBodyTexture);
    UnloadTexture(snakeHeadTexture);
    UnloadRenderTexture(gridTexture);
}


void Renderer::LoadAssets() {
    foodTexture = LoadTexture("assets/apple.png");
    snakeBodyTexture = LoadTexture("assets/snake_body.png");
    snakeHeadTexture = LoadTexture("assets/snake_head.png");
}


RenderTexture2D Renderer::CreateGridTexture(const Grid& grid) {
    gridTexture = LoadRenderTexture(grid.GetWidth() * grid.GetCellSize(), grid.GetHeight() * grid.GetCellSize());

    const int width = grid.GetWidth();
    const int height = grid.GetHeight();
    const int cellSize = grid.GetCellSize();

    BeginTextureMode(gridTexture);

    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            Color c = ((x + y) % 2 == 0) ? cellColor1 : cellColor2;

            DrawRectangle(x * cellSize, y * cellSize, cellSize, cellSize, c);
        }
    }

    EndTextureMode();
    return gridTexture;
}


int Renderer::GetPadding() const {
    return padding;
}


void Renderer::DrawGrid(const Grid& grid) const {
    const Rectangle source{
        .x = 0.0f, .y = 0.0f, .width = static_cast<float>(gridTexture.texture.width),
        .height = -static_cast<float>(gridTexture.texture.height)
    };
    
    const Vector2 position{.x = static_cast<float>(padding), .y = static_cast<float>(padding)};
    DrawTextureRec(gridTexture.texture, source, position, WHITE);
}


void Renderer::DrawSnake(const Snake& snake, const Grid& grid) const {
    const auto& body = snake.GetBody();
    
    for (size_t i = 0; i < body.size(); i++) {
        const Position& position = body[i];

        const int x = position.x * grid.GetCellSize() + padding;
        const int y = position.y * grid.GetCellSize() + padding;

        const Texture2D texture = (i == 0) ? snakeHeadTexture : snakeBodyTexture;
        DrawTexture(texture, x, y, WHITE);
    }
}


void Renderer::DrawFood(const Food& food, const Grid& grid) const {
    Position pos = food.GetPosition();

    DrawTexture(foodTexture, pos.x * grid.GetCellSize() + padding, pos.y * grid.GetCellSize() + padding, WHITE);
}
