
#include "gol_utils.hpp"
#include <execution>

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
}; // namespace

int inc_circular_idx(int current, int inc, int max)
{
    return (current + inc) % max;
}

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

std::optional<std::size_t> detect_period(const std::vector<std::size_t> &v, std::size_t max_period,
                                         std::size_t repetitions_required)
{
    const std::size_t n = v.size();

    for (std::size_t period = 1; period <= max_period && period * repetitions_required <= n; ++period)
    {
        bool matches = true;

        const std::size_t start = n - period * repetitions_required;

        for (std::size_t i = start; i < n - period; ++i)
        {
            if (v[i] != v[i + period])
            {
                matches = false;
                break;
            }
        }

        if (matches)
            return period;
    }

    return std::nullopt;
}
