#include "AI.h"

#include "StateEncoder.h"
#include "StateKey.h"
#include "../game/ActionUtils.h"
#include "raylib.h"


Action AI::GetAction(const GameState& gameState) {
    AIState state = StateEncoder::EncodeGameStateToAIState(gameState);

    StateKey key = EncodeAIStateToKey(state);

    QValues& values = qTable.Get(key);

    std::vector<Action> validActions = GetValidActions(state.direction);

    const float randomValue = GetRandomValue(0, 1000) / 1000.0f;

    if (randomValue < explorationRate)
        return GetRandomAction(validActions);

    return GetBestAction(values, validActions);
}


void AI::SetExplorationRate(float rate) {
    if (rate < 0.0f || rate > 1.0f)
        return;

    explorationRate = rate;
}


float AI::GetExplorationRate() const {
    return explorationRate;
}


size_t AI::GetQTableSize() const {
    return qTable.GetSize();
}


void AI::Learn(const GameState& oldState, Action action, float reward, const GameState& newState) {
    AIState oldAIState = StateEncoder::EncodeGameStateToAIState(oldState);
    AIState newAIState = StateEncoder::EncodeGameStateToAIState(newState);

    StateKey oldKey = EncodeAIStateToKey(oldAIState);
    StateKey newKey = EncodeAIStateToKey(newAIState);

    QValues& oldValues = qTable.Get(oldKey);

    const float currentQ = GetQValue(oldValues, action);

    float target = reward;

    if (!newState.gameOver) {
        QValues& newValues = qTable.Get(newKey);

        std::vector<Action> validActions = GetValidActions(newAIState.direction);

        const float maxNextQ = GetMaxQValue(newValues, validActions);

        target += discountFactor * maxNextQ;
    }

    const float newQ = currentQ + learningRate * (target - currentQ);

    GetQValue(oldValues, action) = newQ;
}


void AI::DecayExploration() {
    explorationRate *= explorationDecay;

    if (explorationRate < minExplorationRate)
        explorationRate = minExplorationRate;
}


void AI::Save(const std::string& filename) const {
    qTable.Save(filename);
}


void AI::Load(const std::string& filename) {
    qTable.Load(filename);
}
