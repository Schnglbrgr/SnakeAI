#include "GameRunner.h"


GameRunner::GameRunner(Game& game, AI& ai, Renderer& renderer) : game(game), ai(ai), renderer(renderer) {
}


void GameRunner::Run() {
    tickTimer = 0.0f;

    const Grid& grid = game.GetGrid();

    InitWindow(grid.GetWidth() * grid.GetCellSize() + renderer.GetPadding() * 2,
               grid.GetHeight() * grid.GetCellSize() + renderer.GetPadding() * 2, "SNAKE AI");
    
    SetTargetFPS(60);

    const Image icon = LoadImage("assets/snake_head.png");
    SetWindowIcon(icon);
    UnloadImage(icon);

    renderer.LoadAssets();
    renderer.CreateGridTexture(grid);

    game.Reset();


    while (!WindowShouldClose()) {
        if (mode == GameRunnerMode::Human)
            HandleHumanInput();

        Tick();
        Render();
    }

    CloseWindow();
}


void GameRunner::SetTickRate(const float ticksPerSecond) {
    if (ticksPerSecond <= 0.0f)
        return;

    tickInterval = 1.0f / ticksPerSecond;
}


void GameRunner::Tick() {
    if (game.IsGameOver()) {
        game.Reset();
        tickTimer = 0.0f;
        return;
    }

    tickTimer += GetFrameTime();
    if (tickTimer < tickInterval)
        return;
    tickTimer -= tickInterval;

    Action action = Action::None;

    if (mode == GameRunnerMode::AI) {
        const GameState state = game.GetGameState();
        action = ai.GetAction(state);
    }
    else if (mode == GameRunnerMode::Human) {
        action = pendingAction;
        pendingAction = Action::None;
    }

    game.Step(action);
}


void GameRunner::SetMode(const GameRunnerMode newMode) {
    mode = newMode;
}


void GameRunner::HandleHumanInput() {
    if (IsKeyPressed(KEY_W))
        pendingAction = Action::Up;

    if (IsKeyPressed(KEY_S))
        pendingAction = Action::Down;

    if (IsKeyPressed(KEY_A))
        pendingAction = Action::Left;

    if (IsKeyPressed(KEY_D))
        pendingAction = Action::Right;
}


void GameRunner::Render() const {
    const Grid& grid = game.GetGrid();
    const Snake& snake = game.GetSnake();
    const Food& food = game.GetFood();

    BeginDrawing();
    ClearBackground(renderer.backgroundColor);

    renderer.DrawGrid(grid);
    renderer.DrawFood(food, grid);
    renderer.DrawSnake(snake, grid);

    DrawHUD();

    EndDrawing();
}


void GameRunner::DrawHUD() const {
    const int padding = renderer.GetPadding();
    constexpr int fontSize = 20;
    constexpr int lineWidth = 200;

    DrawText(TextFormat("Episode: %i", game.GetEpisode()), padding, 10, fontSize, WHITE);
    DrawText(TextFormat("Score: %i", game.GetScore()), padding + lineWidth, 10, fontSize, WHITE);
    DrawText(TextFormat("Best: %i", game.GetBestScore()), padding + lineWidth * 2, 10, fontSize, WHITE);
    DrawText(TextFormat("Steps: %i", game.GetSteps()), padding + lineWidth * 3, 10, fontSize, WHITE);
}
