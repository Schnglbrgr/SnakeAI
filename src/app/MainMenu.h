#pragma once

#include "raylib.h"


enum class MenuAction {
    None,
    Train,
    Watch,
    Play,
    Exit
};


class MainMenu {
public:
    MenuAction Run();

private:
    MenuAction HandleInput() const;
    void Draw() const;
    void SetupButtons();
    void DrawButton(Rectangle rectangle, const char* text) const;

    Rectangle trainButton{};
    Rectangle watchButton{};
    Rectangle playButton{};
    Rectangle exitButton{};
};
