#pragma once

#include "game/Game.h"
#include "ai/AI.h"
#include "rendering/Renderer.h"


enum class GameRunnerMode {
    AI, Human
};


class GameRunner {
public:
    GameRunner(Game& game, AI& ai, Renderer& renderer);

    void Run();

    void SetTickRate(float ticksPerSecond);
    void SetMode(GameRunnerMode mode);

private:
    void Tick();
    void Render();
    void HandleHumanInput();
    
    void DrawHUD() const;

    Game& game;
    AI& ai;
    Renderer& renderer;

    GameRunnerMode mode = GameRunnerMode::AI;
    
    float tickTimer = 0.0f;
    float tickInterval = 0.2f;
    
    Action pendingAction = Action::None;
};
