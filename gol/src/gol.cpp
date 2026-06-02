
#include "gol.hpp"
#include <vector>

#define IN_BOUNDS_INC(V, LOWER, UPPER) ((V) >= (LOWER) && (V) <= (UPPER))

BoolMat::BoolMat(int height, int width) : _height(height), _width(width), _mat()
{
    for (int i = 0; i < height; i++)
    {
        _mat.push_back(std::vector<bool>(_width, false));
    }
}

BoolMat::~BoolMat() = default;

int BoolMat::GetHeight() const
{
    return _height;
}

int BoolMat::GetWidth() const
{
    return _width;
};

BoolMat::BoolMat(const BoolMat &other)
{
    _width = other._width;
    _height = other._height;
    for (int i = 0; i < _height; i++)
    {
        _mat.push_back(std::vector<bool>(other._mat[i]));
    }
}

bool BoolMat::GetCell(int x, int y) const
{
    if (!IN_BOUNDS_INC(x, 0, _width) || !IN_BOUNDS_INC(y, 0, _height))
    {
        return false;
    }
    return _mat[y][x];
}

void BoolMat::SetCell(int x, int y, bool value)
{
    if (!IN_BOUNDS_INC(x, 0, _width) || !IN_BOUNDS_INC(y, 0, _height))
    {
        return;
    }
    _mat[y][x] = value;
}

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

void GolEvaluateCell(int x, int y, const BoolMat &currentGen, BoolMat &nextGen, BoolMat &visited)
{
    if (visited.GetCell(x, y))
    {
        return;
    }

    visited.SetCell(x, y, true);

    int neighbours = 0;
    for (auto move : moves)
    {
        neighbours += currentGen.GetCell(x + move.x, y + move.y);
    }

    bool alive = currentGen.GetCell(x, y);

    if (not alive)
    {
        if (neighbours == 3)
        {
            nextGen.SetCell(x, y, true); // Cell Reproduction
        }
        return;
    }

    if (neighbours < 2 || neighbours > 3)
    {
        nextGen.SetCell(x, y, false); // The Cell Dies
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

void GolTick(BoolMat &golMat)
{
    BoolMat visited(golMat.GetHeight(), golMat.GetWidth());
    const BoolMat currentGen(golMat);
    for (int y = 0; y < golMat.GetHeight(); y++)
    {
        for (int x = 0; x < golMat.GetWidth(); x++)
        {
            if (golMat.GetCell(x, y))
            {
                GolEvaluateCell(x, y, currentGen, golMat, visited);
            }
        }
    }
}
