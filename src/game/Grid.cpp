#include "Grid.h"

Grid::Grid(int w, int h, int c) {
    width = w;
    height = h;
    cellSize = c;
}

int Grid::GetCellSize() const {
    return cellSize;
};

int Grid::GetHeight() const {
    return height;
}

int Grid::GetWidth() const {
    return width;
}
