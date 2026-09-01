#include "Game.h"
#include "RewardSystem.h"


Game::Game() : grid(15, 10, 64), snake(3, 4), rng(std::random_device{}()) {
}


const Grid& Game::GetGrid() const {
    return grid;
}


const Snake& Game::GetSnake() const {
    return snake;
}


const Food& Game::GetFood() const {
    return food;
}


int Game::GetEpisode() const {
    return episode;
}


int Game::GetScore() const {
    return score;
}


int Game::GetBestScore() const {
    return bestScore;
}


int Game::GetSteps() const {
    return steps;
}


StepResult Game::Step(const Action action) {
    if (gameOver)
        return {.state = GetGameState(), .reward = 0.0f, .done = true,};

    if (action != Action::None)
        ApplyAction(action);

    snake.Move();
    steps++;

    const CollisionType collision = CheckCollision();
    const float reward = RewardSystem::GetReward(collision);

    return {.state = GetGameState(), .reward = reward, .done = gameOver};
}


void Game::Reset() {
    episode++;

    gameOver = false;

    score = 0;
    steps = 0;

    snake.Reset(3, 4);
    SpawnFood();
}


bool Game::IsGameOver() const {
    return gameOver;
}


GameState Game::GetGameState() const {
    GameState state;

    state.snakeBody = snake.GetBody();
    state.foodPosition = food.GetPosition();

    state.gridWidth = grid.GetWidth();
    state.gridHeight = grid.GetHeight();

    state.direction = snake.GetDirection();

    state.gameOver = gameOver;

    return state;
}


CollisionType Game::CheckCollision() {
    const CollisionType collision = CollisionSystem::Check(grid, snake, food);

    switch (collision) {
    case CollisionType::Wall:
    case CollisionType::Self:
        gameOver = true;
        break;

    case CollisionType::Food:
        snake.Grow();
        score++;

        if (score > bestScore)
            bestScore = score;

        SpawnFood();
        break;

    case CollisionType::None:
        break;
    }

    return collision;
}


void Game::ApplyAction(const Action action) {
    switch (action) {
    case Action::Up:
        snake.ChangeDirection(Direction::Up);
        break;

    case Action::Down:
        snake.ChangeDirection(Direction::Down);
        break;

    case Action::Left:
        snake.ChangeDirection(Direction::Left);
        break;

    case Action::Right:
        snake.ChangeDirection(Direction::Right);
        break;
    }
}


void Game::SpawnFood() {
    std::uniform_int_distribution<int> xDistribution(0, grid.GetWidth() - 1);
    std::uniform_int_distribution<int> yDistribution(0, grid.GetHeight() - 1);

    Position position{};

    do {
        position.x = xDistribution(rng);
        position.y = yDistribution(rng);
    }
    while (snake.OccupiesPosition(position));

    food.SetPosition(position.x, position.y);
}
