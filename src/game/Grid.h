#pragma once


class Grid
{
public:
    Grid(int w, int h, int c);

    int GetWidth() const;
    int GetHeight() const;
    int GetCellSize() const;

private:
    int cellSize;
    int width;
    int height;
};
