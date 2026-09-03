#pragma once

#include "raylib.h"


enum class MenuAction {
    None,
    Train,
    Watch,
    Play,
    Exit,
    Reset
};


class MainMenu {
public:
    MenuAction Run();

    int GetEpisodeCount() const;

private:
    void ShowResetTooltip(Rectangle rec) const;
    MenuAction HandleInput() const;
    void Draw() const;
    void SetupButtons();
    void DrawButton(Rectangle rectangle, const char* buttonText) const;
    void DrawInputField() const;
    void HandleTextInput();
    void SetDefaultEpisodes();

    const Color hoveredColor = {.r = 0, .g = 51, .b = 0, .a = 255};
    const Color defaultColor = {.r = 0, .g = 102, .b = 0, .a = 255};

    Texture2D gridTexture{};
    Texture2D trashBinTexture{};

    Rectangle trainButton{};
    Rectangle watchButton{};
    Rectangle playButton{};
    Rectangle exitButton{};
    
    Rectangle resetButton{};

    Rectangle textBox{};
    int letterCount = 0;

    static constexpr int maxInputCount = 5;
    char text[maxInputCount + 1] = "\0";
    int framesCounter = 0;
    bool mouseOnText = false;
};
