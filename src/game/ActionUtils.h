#pragma once


#include <vector>

#include "Action.h"
#include "Direction.h"

std::vector<Action> GetValidActions(Direction direction);

Action GetRandomAction(const std::vector<Action>& actions);


class ActionUtils {
};
