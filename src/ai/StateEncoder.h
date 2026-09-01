#pragma once

#include "../game/AIState.h"
#include "../game/GameState.h"


class StateEncoder {
public:
    static AIState EncodeGameStateToAIState(const GameState& gameState);
};
