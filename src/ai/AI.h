#pragma once

#include "../game/GameState.h"
#include "QTable.h"
#include "../game/Action.h"


class AI {
public:
    Action GetAction(const GameState& gameState);

    void Learn(const GameState& oldState, Action action, float reward, const GameState& newState);

    void SetExplorationRate(float rate);
    float GetExplorationRate() const;
    
    size_t GetQTableSize() const;
    
    void DecayExploration();

    void Save(const std::string& filename) const;
    void Load(const std::string& filename);

private:
    QTable qTable;

    float explorationRate = 1.0f;
    float minExplorationRate = 0.05f;
    float explorationDecay = 0.995f;

    float learningRate = 0.1f;
    float discountFactor = 0.90f;
};
