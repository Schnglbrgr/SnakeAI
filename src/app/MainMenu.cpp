#include "MainMenu.h"


MenuAction MainMenu::Run() {
    InitWindow(900, 600, "Snake AI");
    SetTargetFPS(60);

    SetupButtons();

    while (!WindowShouldClose()) {
        const MenuAction action = HandleInput();

        if (action != MenuAction::None) {
            CloseWindow();
            return action;
        }

        BeginDrawing();
        ClearBackground(BLACK);
        Draw();
        EndDrawing();
    }

    CloseWindow();
    return MenuAction::Exit;
}


void MainMenu::Draw() const {
    const int screenWidth = GetScreenWidth();

    DrawText("SNAKE", screenWidth / 2 - MeasureText("SNAKE", 60) / 2, 70, 60, WHITE);
    DrawText("AI", screenWidth / 2 - MeasureText("AI", 40) / 2, 135, 40, LIGHTGRAY);

    DrawButton(trainButton, "TRAIN AI");
    DrawButton(watchButton, "WATCH AI");
    DrawButton(playButton, "PLAY SNAKE");
    DrawButton(exitButton, "EXIT");
}


void MainMenu::SetupButtons() {
    const float buttonWidth = 300.0f;
    const float buttonHeight = 55.0f;

    const float x = GetScreenWidth() / 2.0f - buttonWidth / 2.0f;

    trainButton = {x, 210.0f, buttonWidth, buttonHeight};
    watchButton = {x, 280.0f, buttonWidth, buttonHeight};
    playButton = {x, 350.0f, buttonWidth, buttonHeight};
    exitButton = {x, 420.0f, buttonWidth, buttonHeight};
}


void MainMenu::DrawButton(const Rectangle rectangle, const char* text) const {
    DrawRectangleRec(rectangle, DARKGREEN);

    const int fontSize = 22;
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
