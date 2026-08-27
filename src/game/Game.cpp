#include "Game.h"
#include "raylib.h"

Game::Game() : grid(15, 10, 64) {
}

void Game::Run() {
    InitWindow(grid.GetWidth() * grid.GetCellSize(), grid.GetHeight() * grid.GetCellSize(), "SNAKE AI");
    SetTargetFPS(60);

    renderer.LoadAssets();
    renderer.CreateGridTexture(grid);
    food = Food();
    food.SetPosition(7, 4);

    while (!WindowShouldClose())
    {
        Render(food, grid);
    }

    CloseWindow();
}

void Game::Render(const Food& food, const Grid& grid) {
    BeginDrawing();
    ClearBackground(BLACK);

    renderer.DrawGrid();
    renderer.DrawFood(food, grid);

    EndDrawing();
}

void Game::SpawnFood() {
    int x = GetRandomValue(0, grid.GetWidth() - 1);
    int y = GetRandomValue(0, grid.GetHeight() - 1);

    food.SetPosition(x, y);
}
