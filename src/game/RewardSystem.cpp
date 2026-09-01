#include "RewardSystem.h"


float RewardSystem::GetReward(CollisionType collision) {
    switch (collision) {
    case CollisionType::Food:
        return 10.0f;

    case CollisionType::Self:
    case CollisionType::Wall:
        return -10.0f;

    case CollisionType::None:
        return -0.1f;

        return 0.0f;
    }
}
