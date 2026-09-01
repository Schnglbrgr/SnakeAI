#include "StateEncoder.h"


namespace {
    bool IsDangerous(const GameState& gameState, const Position& position) {
        if (position.x < 0 || position.x >= gameState.gridWidth || position.y < 0 || position.y >= gameState.gridHeight) {
            return true;
        }

        for (const Position& bodyPart : gameState.snakeBody) {
            if (bodyPart == position)
                return true;
        }

        return false;
    }
}


AIState StateEncoder::EncodeGameStateToAIState(const GameState& gameState) {
    AIState state{};

    const Position& head = gameState.snakeBody.front();

    state.direction = gameState.direction;

    state.foodUp = gameState.foodPosition.y < head.y;
    state.foodDown = gameState.foodPosition.y > head.y;
    state.foodLeft = gameState.foodPosition.x < head.x;
    state.foodRight = gameState.foodPosition.x > head.x;

    state.dangerUp = IsDangerous(gameState, {.x = head.x, .y = head.y - 1});
    state.dangerDown = IsDangerous(gameState, {.x = head.x, .y = head.y + 1});
    state.dangerLeft = IsDangerous(gameState, {.x = head.x - 1, .y = head.y});
    state.dangerRight = IsDangerous(gameState, {.x = head.x + 1, .y = head.y});

    return state;
}
