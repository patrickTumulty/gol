
#include "gol_randomizer.hpp"
#include <random>


void randomize_gol_board(gol &gol, std::uint32_t seed)
{
    std::mt19937 gen(seed);

    double density = 0.0;

    switch (seed % 4)
    {
    case 0:
        // Sparse
        density = 0.1;
        break;

    case 1:
        // Dense
        density = 0.6;
        break;

    case 2:
        // Medium
        density = 0.3;
        break;

    case 3:
        // Random density
        density = std::uniform_real_distribution<double>(0.05, 0.95)(gen);
        break;
    }

    std::bernoulli_distribution alive(density);

    for (int y = 0; y < gol.height(); ++y)
    {
        for (int x = 0; x < gol.width(); ++x)
        {
            gol.set_cell(x, y, alive(gen));
        }
    }
}
