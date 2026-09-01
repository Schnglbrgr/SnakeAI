#include "ActionUtils.h"

#include "raylib.h"


std::vector<Action> GetValidActions(const Direction direction) {
    switch (direction) {
    case Direction::Up:
        return {Action::Up, Action::Left, Action::Right};

    case Direction::Down:
        return {Action::Down, Action::Left, Action::Right};

    case Direction::Left:
        return {Action::Left, Action::Up, Action::Down};

    case Direction::Right:
        return {Action::Right, Action::Up, Action::Down};
    }

    return {};
}


Action GetRandomAction(const std::vector<Action>& actions) {
    const int index = GetRandomValue(0, actions.size() - 1);
    return actions[index];
}
