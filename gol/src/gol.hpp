
#ifndef GOL_HPP
#define GOL_HPP

#include "mat.hpp"

#define SEQUENCE_DETECT_LEN 20

class gol
{
  public:
    gol(int height, int width);
    ~gol() = default;

    bool tick();

    void set_cell(int x, int y, bool value);
    std::optional<bool> get_cell(int x, int y) const;

    int height() const;
    int width() const;
    int total_generations() const;

  private:
    bool check_for_seqence();

    mat<bool> _gol_state;
    mat<bool> _gol_copy;
    mat<bool> _visited;

    int _total_generations = 0;
    int _current_cell_count = 0;
    std::size_t _generation_hash = 0;
    std::size_t _sequence_detect[SEQUENCE_DETECT_LEN];
    int _seqence_detect_idx = 0;
};

void gol_tick(mat<bool> &golMat);

#endif // GOL_HPP
