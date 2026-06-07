
#include "gol.hpp"
#include <cstdio>

namespace
{
struct move
{
    int x;
    int y;
};

static move moves[] = {
    {1, 0},   //
    {0, 1},   //
    {-1, 0},  //
    {0, -1},  //
    {1, 1},   //
    {-1, 1},  //
    {1, -1},  //
    {-1, -1}, //
};

void gol_eval_cell(int x, int y, const mat<bool> &currentGen, mat<bool> &nextGen, mat<bool> &visited)
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
        gol_eval_cell(x + move.x, y + move.y, currentGen, nextGen, visited);
    }
}

void clear_mat(mat<bool> &m)
{
    for (int i = 0; i < m.height(); i++)
    {
        for (int j = 0; j < m.width(); j++)
        {
            m.set_cell(j, i, false);
        }
    }
}

void copy_mat(mat<bool> &dest, const mat<bool> &src)
{
    for (int y = 0; y < src.height(); y++)
    {
        for (int x = 0; x < src.width(); x++)
        {
            dest.set_cell(x, y, src.get_cell(x, y).value_or(false));
        }
    }
}

int count_live_cells(const mat<bool> &m)
{
    int count = 0;
    for (int y = 0; y < m.height(); y++)
    {
        for (int x = 0; x < m.width(); x++)
        {
            if (m.get_cell(x, y).value_or(false))
            {
                count++;
            }
        }
    }
    return count;
}

std::size_t hash_mat(const mat<bool> &m)
{
    std::size_t hash = 0;

    for (int y = 0; y < m.height(); y++)
    {
        for (int x = 0; x < m.width(); x++)
        {
            bool b = m.get_cell(x, y).value_or(false);
            hash ^= std::hash<bool>{}(b) + 0x9e3779b9 + (hash << 6) + (hash >> 2);
        }
    }

    return hash;
}

}; // namespace

gol::gol(int height, int width)
    : _gol_state(height, width, false), _gol_copy(height, width, false), _visited(height, width, false)
{
}

int gol::height() const
{
    return _gol_state.height();
}

int gol::width() const
{
    return _gol_state.width();
}

void gol::set_cell(int x, int y, bool value)
{
    _gol_state.set_cell(x, y, value);
}

std::optional<bool> gol::get_cell(int x, int y) const
{
    return _gol_state.get_cell(x, y);
}

void gol::tick()
{
    clear_mat(_visited);
    copy_mat(_gol_copy, _gol_state);
    for (int y = 0; y < _gol_state.height(); y++)
    {
        for (int x = 0; x < _gol_state.width(); x++)
        {
            if (_gol_state.get_cell(x, y).value_or(false))
            {
                gol_eval_cell(x, y, _gol_copy, _gol_state, _visited);
            }
        }
    }
}
