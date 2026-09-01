#pragma once


#include <random>
#include "GameState.h"
#include "Action.h"
#include "CollisionType.h"
#include "Food.h"
#include "Grid.h"
#include "Snake.h"
#include "StepResult.h"


class Game {
public:
    Game();

    void Reset();
    StepResult Step(Action action);
    GameState GetGameState() const;
    bool IsGameOver() const;

    const Grid& GetGrid() const;
    const Snake& GetSnake() const;
    const Food& GetFood() const;

    int GetEpisode() const;
    int GetScore() const;
    int GetBestScore() const;
    int GetSteps() const;

private:
    CollisionType CheckCollision();
    void SpawnFood();
    void ApplyAction(Action action);

    bool gameOver = false;

    Grid grid;
    Snake snake;
    Food food;

    int episode = 0;
    int score = 0;
    int bestScore = 0;
    int steps = 0;

    std::mt19937 rng;
};
