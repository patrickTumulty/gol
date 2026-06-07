
#ifndef GOL_UTILS_HPP
#define GOL_UTILS_HPP

#include "mat.hpp"

void gol_eval_cell(int x, int y, const mat<bool> &currentGen, mat<bool> &nextGen, mat<bool> &visited);
void clear_mat(mat<bool> &m);
void copy_mat(mat<bool> &dest, const mat<bool> &src);
int count_live_cells(const mat<bool> &m);
std::size_t hash_mat(const mat<bool> &m);
int inc_circular_idx(int current, int inc, int max);
std::optional<std::size_t> detect_period(const std::vector<std::size_t> &v, //
                                         std::size_t max_period = 15,       //
                                         std::size_t repetitions_required = 3);

#endif // GOL_UTILS_HPP
