#include "MainMenu.h"

#include <string>


MenuAction MainMenu::Run() {
    InitWindow(960, 640, "Snake AI");
    SetTargetFPS(60);

    Image icon = LoadImage("assets/snake_head.png");
    SetWindowIcon(icon);
    UnloadImage(icon);

    gridTexture = LoadTexture("assets/grid.png");
    trashBinTexture = LoadTexture("assets/trashBin.png");

    SetupButtons();
    SetDefaultEpisodes();

    while (!WindowShouldClose()) {
        if (const MenuAction action = HandleInput(); action != MenuAction::None) {
            UnloadTexture(gridTexture);
            UnloadTexture(trashBinTexture);
            CloseWindow();
            return action;
        }

        HandleTextInput();

        BeginDrawing();
        ClearBackground(BLACK);
        Draw();
        EndDrawing();
    }

    UnloadTexture(gridTexture);
    UnloadTexture(trashBinTexture);
    CloseWindow();
    return MenuAction::Exit;
}


void MainMenu::Draw() const {
    const int screenWidth = GetScreenWidth();

    DrawTexture(gridTexture, 0, 0, WHITE);

    DrawText("SNAKE", screenWidth / 2 - MeasureText("SNAKE", 60) / 2, 70, 60, WHITE);
    DrawText("AI", screenWidth / 2 - MeasureText("AI", 40) / 2, 135, 40, WHITE);

    DrawButton(trainButton, "TRAIN AI");
    DrawButton(watchButton, "WATCH AI");
    DrawButton(playButton, "PLAY SNAKE");
    DrawButton(exitButton, "EXIT");
    DrawButton(resetButton, "");

    const int trashBinX = resetButton.x + (resetButton.width - trashBinTexture.width) / 2;
    const int trashBinY = resetButton.y + (resetButton.height - trashBinTexture.height) / 2;

    DrawTexture(trashBinTexture, trashBinX, trashBinY, WHITE);

    if (CheckCollisionPointRec(GetMousePosition(), resetButton))
        ShowResetTooltip(resetButton);

    DrawInputField();
}


void MainMenu::SetupButtons() {
    constexpr float buttonWidth = 300.0f;
    constexpr float buttonHeight = 60.0f;

    constexpr float textBoxWidth = 150.0f;
    constexpr float textBoxHeight = 50.0f;

    const float x = static_cast<float>(GetScreenWidth()) / 2.0f - buttonWidth / 2.0f;

    trainButton = {x, 280.0f, buttonWidth, buttonHeight};
    watchButton = {x, 350.0f, buttonWidth, buttonHeight};
    playButton = {x, 420.0f, buttonWidth, buttonHeight};
    exitButton = {x, 490.0f, buttonWidth, buttonHeight};
    resetButton = {trainButton.x + trainButton.width + 10.0f, trainButton.y + 5.0f, 50.0f, 50.0f};
    textBox = {static_cast<float>(GetScreenWidth()) / 2.0f, 210.0f, textBoxWidth, textBoxHeight};
}


void MainMenu::DrawButton(const Rectangle rectangle, const char* buttonText) const {
    const Vector2 mousePosition = GetMousePosition();

    const bool isHovered = CheckCollisionPointRec(mousePosition, rectangle);

    Rectangle drawRectangle = rectangle;

    if (isHovered) {
        constexpr float padding = 4.0f;
        drawRectangle.x -= padding;
        drawRectangle.y -= padding;
        drawRectangle.width += padding * 2.0f;
        drawRectangle.height += padding * 2.0f;
    }

    const Color buttonColor = isHovered ? hoveredColor : defaultColor;

    DrawRectangleRounded(drawRectangle, 0.5f, 4, buttonColor);

    constexpr int fontSize = 22;
    const int textWidth = MeasureText(buttonText, fontSize);

    const float textX = rectangle.x + rectangle.width / 2.0f - static_cast<float>(textWidth) / 2.0f;
    const float textY = rectangle.y + rectangle.height / 2.0f - fontSize / 2.0f;

    DrawText(buttonText, static_cast<int>(textX), static_cast<int>(textY), fontSize, WHITE);
}


void MainMenu::DrawInputField() const {
    constexpr int fontSize = 22;
    const int textX = static_cast<int>(textBox.x) + 10;
    const int textY = static_cast<int>(textBox.y + textBox.height / 2.0f - fontSize / 2.0f);

    DrawText("Episodes", GetScreenWidth() / 2 - 150,
             static_cast<int>(textBox.y) + static_cast<int>(textBox.height) / 2 - 16, 32, WHITE);

    DrawRectangleRounded(textBox, 0.3f, 4, defaultColor);

    DrawText(text, textX, textY, fontSize, WHITE);

    if (mouseOnText) {
        if (framesCounter / 20 % 2 == 0) {
            const int cursorX = textX + MeasureText(text, fontSize);
            DrawText("|", cursorX + 2, textY, fontSize, WHITE);
        }
    }
}


void MainMenu::HandleTextInput() {
    if (CheckCollisionPointRec(GetMousePosition(), textBox) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        mouseOnText = true;

    if (!CheckCollisionPointRec(GetMousePosition(), textBox) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        mouseOnText = false;

    if (mouseOnText) {
        SetMouseCursor(MOUSE_CURSOR_IBEAM);

        framesCounter++;

        int key = GetCharPressed();

        while (key > 0) {
            if (key >= '0' && key <= '9' && letterCount < maxInputCount) {
                text[letterCount] = static_cast<char>(key);
                text[letterCount + 1] = '\0';
                letterCount++;
            }
            key = GetCharPressed();
        }

        if (IsKeyPressed(KEY_BACKSPACE)) {
            letterCount--;
            if (letterCount < 0)
                letterCount = 0;
            text[letterCount] = '\0';
        }
    }
    else {
        SetMouseCursor(MOUSE_CURSOR_DEFAULT);
        framesCounter = 0;
    }
}


void MainMenu::SetDefaultEpisodes() {
    constexpr char defaultEpisodeCount[] = "10000";
    letterCount = 0;

    for (int i = 0; i < maxInputCount; i++) {
        text[letterCount] = defaultEpisodeCount[i];
        text[letterCount + 1] = '\0';
        letterCount++;
    }
}


int MainMenu::GetEpisodeCount() const {
    if (letterCount == 0)
        return 1;

    const int episodes = std::stoi(text);

    return std::max(episodes, 1);
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

    if (CheckCollisionPointRec(mousePosition, resetButton)) {
        return MenuAction::Reset;
    }

    return MenuAction::None;
}


void MainMenu::ShowResetTooltip(Rectangle rec) const {
    constexpr auto resetTooltip = "Deletes the saved QTable";
    DrawText(resetTooltip, static_cast<int>(resetButton.x) + 5, static_cast<int>(resetButton.y - 30), 22, WHITE);
}
