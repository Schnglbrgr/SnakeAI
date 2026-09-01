#include "StateKey.h"

StateKey EncodeAIStateToKey(const AIState& state)
{
    StateKey key = 0;

    key |= state.dangerUp    << 0;
    key |= state.dangerDown  << 1;
    key |= state.dangerLeft  << 2;
    key |= state.dangerRight << 3;

    key |= state.foodUp      << 4;
    key |= state.foodDown    << 5;
    key |= state.foodLeft    << 6;
    key |= state.foodRight   << 7;

    key |= static_cast<StateKey>(state.direction) << 8;

    return key;
}