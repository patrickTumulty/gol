
#ifndef GOL_HPP
#define GOL_HPP

#include "mat.hpp"

enum gol_end_state
{
    UNDETERMINED,
    DESTRUCTION,
    STABILITY
};

class gol
{
  public:
    gol(int height, int width);
    ~gol() ;

    bool tick();

    void set_cell(int x, int y, bool value);
    std::optional<bool> get_cell(int x, int y) const;

    int height() const;
    int width() const;
    int total_generations() const;
    std::optional<int> stable_period() const;
    gol_end_state end_state() const;

  private:
    bool check_for_seqence();

    mat<bool> _gol_state;
    mat<bool> _gol_copy;
    mat<bool> _visited;

    int _total_generations = 0;
    int _current_cell_count = 0;
    std::size_t _generation_hash = 0;
    std::vector<std::size_t> _sequence_detect;
    int _seqence_detect_idx = 0;
    gol_end_state _end_state = UNDETERMINED;
    std::optional<int> _stable_period = {};
};

#endif // GOL_HPP
