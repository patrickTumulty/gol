
#include "gol.hpp"
#include "gol_utils.hpp"
#include <cstdio>

#define SEQUENCE_DETECT_BUFFER_SIZE 30

gol::gol(int height, int width)         //
    : _gol_state(height, width, false), //
      _gol_copy(height, width, false),  //
      _visited(height, width, false),   //
      _sequence_detect(SEQUENCE_DETECT_BUFFER_SIZE, 0)
{
}

gol::~gol() = default;

int gol::height() const
{
    return _gol_state.height();
}

int gol::width() const
{
    return _gol_state.width();
}

int gol::total_generations() const
{
    return _total_generations;
}

void gol::set_cell(int x, int y, bool value)
{
    _gol_state.set_cell(x, y, value);
}

std::optional<int> gol::stable_period() const
{
    return _stable_period;
}

gol_end_state gol::end_state() const
{
    return _end_state;
}

std::optional<bool> gol::get_cell(int x, int y) const
{
    return _gol_state.get_cell(x, y);
}

bool gol::check_for_seqence()
{
    auto period = detect_period(_sequence_detect, 15, 2);
    if (period.has_value())
    {
        _end_state = STABILITY;
        _stable_period = period.value();
        return true;
    }
    return false;
}

bool gol::tick()
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
    _total_generations++;
    _seqence_detect_idx = inc_circular_idx(_seqence_detect_idx, 1, _sequence_detect.size());
    _sequence_detect[_seqence_detect_idx] = hash_mat(_gol_state);
    _current_cell_count = count_live_cells(_gol_state);
    bool sequence_present = false;
    if (_total_generations % SEQUENCE_DETECT_BUFFER_SIZE == 0)
    {
        sequence_present = check_for_seqence();
    }
    if (_end_state == STABILITY)
    {
        return false;
    }
    if (_current_cell_count == 0)
    {
        _end_state = DESTRUCTION;
        return false;
    }
    return true;
}
