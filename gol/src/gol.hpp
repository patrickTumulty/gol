
#ifndef GOL_HPP
#define GOL_HPP

#include "mat.hpp"

class gol
{
  public:
    gol(int height, int width);
    ~gol() = default;

    void tick();

    void set_cell(int x, int y, bool value);
    std::optional<bool> get_cell(int x, int y) const;

    int height() const;
    int width() const;

  private:


    mat<bool> _gol_state;
    mat<bool> _gol_copy;
    mat<bool> _visited;

    int _total_generations;
    std::size_t _generation_hash;
};

void gol_tick(mat<bool> &golMat);

#endif // GOL_HPP
