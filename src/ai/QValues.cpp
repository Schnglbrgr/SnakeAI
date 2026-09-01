#include "QValues.h"


float& GetQValue(QValues& values, Action action) {
    switch (action) {
    case Action::Up:
        return values.up;

    case Action::Down:
        return values.down;

    case Action::Left:
        return values.left;

    case Action::Right:
        return values.right;
    }

    return values.up;
}


float GetQValue(const QValues& values, const Action action) {
    switch (action) {
    case Action::Up:
        return values.up;

    case Action::Down:
        return values.down;

    case Action::Left:
        return values.left;

    case Action::Right:
        return values.right;
    }

    return values.up;
}


Action GetBestAction(const QValues& values, const std::vector<Action>& validActions) {
    Action bestAction = validActions[0];
    float bestValue = GetQValue(values, bestAction);

    for (const Action action : validActions) {
        const float value = GetQValue(values, action);

        if (value > bestValue) {
            bestValue = value;
            bestAction = action;
        }
    }

    return bestAction;
}


float GetMaxQValue(const QValues& values, const std::vector<Action>& validActions) {
    float maxValue = GetQValue(values, validActions[0]);

    for (const Action action : validActions) {
        const float value = GetQValue(values, action);

        if (value > maxValue)
            maxValue = value;
    }

    return maxValue;
}
