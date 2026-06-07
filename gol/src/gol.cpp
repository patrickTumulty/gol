
#include "gol.hpp"
#include <cstdio>

namespace
{
struct Move
{
    int x;
    int y;
};

static Move moves[] = {
    {1, 0},   //
    {0, 1},   //
    {-1, 0},  //
    {0, -1},  //
    {1, 1},   //
    {-1, 1},  //
    {1, -1},  //
    {-1, -1}, //
};

void GolEvaluateCell(int x, int y, const mat<bool> &currentGen, mat<bool> &nextGen, mat<bool> &visited)
{
    if (visited.get_cell(x, y).value_or(true))
    {
        return;
    }

    visited.set_cell(x, y, true);

    int neighbours = 0;
    for (auto move : moves)
    {
        neighbours += currentGen.get_cell(x + move.x, y + move.y).value_or(0);
    }

    bool alive = currentGen.get_cell(x, y).value_or(false);

    if (not alive)
    {
        if (neighbours == 3)
        {
            nextGen.set_cell(x, y, true); // Cell Reproduction
        }
        return;
    }

    if (neighbours < 2 || neighbours > 3)
    {
        nextGen.set_cell(x, y, false); // The Cell Dies
    }
    else if (neighbours == 2 || neighbours == 3)
    {
        // The Cell Lives
    }

    for (auto move : moves)
    {
        GolEvaluateCell(x + move.x, y + move.y, currentGen, nextGen, visited);
    }
}
}; // namespace

void GolTick(mat<bool> &golMat)
{
    mat<bool> visited(golMat.height(), golMat.width(), false);
    const mat<bool> currentGen(golMat);

    for (int y = 0; y < golMat.height(); y++)
    {
        for (int x = 0; x < golMat.width(); x++)
        {
            if (golMat.get_cell(x, y).value_or(false))
            {
                GolEvaluateCell(x, y, currentGen, golMat, visited);
            }
        }
    }
}
