#pragma once

#include <vector>
#include "../game/Action.h"


struct QValues {
    float up = 0.0f;
    float down = 0.0f;
    float left = 0.0f;
    float right = 0.0f;
};


float& GetQValue(QValues& values, Action action);

float GetQValue(const QValues& values, Action action);

Action GetBestAction(const QValues& values, const std::vector<Action>& validActions);

float GetMaxQValue(const QValues& values, const std::vector<Action>& validActions);
