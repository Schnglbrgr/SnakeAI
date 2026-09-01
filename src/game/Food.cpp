#include "Food.h"

Food::Food() {
}

Position Food::GetPosition() const {
    return position;
}

void Food::SetPosition(int x, int y) {
    position.x = x;
    position.y = y;
}
