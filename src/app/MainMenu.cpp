#include "MainMenu.h"


MenuAction MainMenu::Run() {
    InitWindow(960, 640, "Snake AI");
    SetTargetFPS(60);

    Image icon = LoadImage("assets/snake_head.png");
    SetWindowIcon(icon);
    UnloadImage(icon);

    gridTexture = LoadTexture("assets/grid.png");

    SetupButtons();

    while (!WindowShouldClose()) {
        const MenuAction action = HandleInput();

        if (action != MenuAction::None) {
            UnloadTexture(gridTexture);
            CloseWindow();
            return action;
        }

        BeginDrawing();
        ClearBackground(BLACK);
        Draw();
        EndDrawing();
    }

    UnloadTexture(gridTexture);
    CloseWindow();
    return MenuAction::Exit;
}


void MainMenu::Draw() const {
    const int screenWidth = GetScreenWidth();

    DrawTexture(gridTexture, 0, 0, WHITE);

    DrawText("SNAKE", screenWidth / 2 - MeasureText("SNAKE", 60) / 2, 90, 60, WHITE);
    DrawText("AI", screenWidth / 2 - MeasureText("AI", 40) / 2, 155, 40, WHITE);

    DrawButton(trainButton, "TRAIN AI");
    DrawButton(watchButton, "WATCH AI");
    DrawButton(playButton, "PLAY SNAKE");
    DrawButton(exitButton, "EXIT");
}


void MainMenu::SetupButtons() {
    constexpr float buttonWidth = 300.0f;
    constexpr float buttonHeight = 60.0f;

    const float x = GetScreenWidth() / 2.0f - buttonWidth / 2.0f;

    trainButton = {x, 230.0f, buttonWidth, buttonHeight};
    watchButton = {x, 300.0f, buttonWidth, buttonHeight};
    playButton = {x, 370.0f, buttonWidth, buttonHeight};
    exitButton = {x, 440.0f, buttonWidth, buttonHeight};
}


void MainMenu::DrawButton(const Rectangle rectangle, const char* text) const {
    DrawRectangleRounded(rectangle, 0.5f, 4, DARKGREEN);

    constexpr int fontSize = 22;
    const int textWidth = MeasureText(text, fontSize);

    const float textX = rectangle.x + rectangle.width / 2.0f - textWidth / 2.0f;
    const float textY = rectangle.y + rectangle.height / 2.0f - fontSize / 2.0f;

    DrawText(text, static_cast<int>(textX), static_cast<int>(textY), fontSize, WHITE);
}


MenuAction MainMenu::HandleInput() const {
    if (!IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        return MenuAction::None;

    const Vector2 mousePosition = GetMousePosition();

    if (CheckCollisionPointRec(mousePosition, trainButton))
        return MenuAction::Train;

    if (CheckCollisionPointRec(mousePosition, watchButton))
        return MenuAction::Watch;

    if (CheckCollisionPointRec(mousePosition, playButton))
        return MenuAction::Play;

    if (CheckCollisionPointRec(mousePosition, exitButton))
        return MenuAction::Exit;

    return MenuAction::None;
}
