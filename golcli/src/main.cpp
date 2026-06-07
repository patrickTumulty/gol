

#include "gol.hpp"
#include <clocale>
#include <cstdint>
#include <cstdio>
#include <ncurses.h>
#include <ncursesw/ncurses.h>
#include <random>
#include <thread>

int alt = 0;
int cols = 0;
int rows = 0;

void draw_tiles(gol &gol)
{
    for (int i = 0; i < gol.height(); i++)
    {
        for (int j = 0; j < gol.width(); j++)
        {
            if (gol.get_cell(j, i).value_or(false))
            {
                mvaddch(i, j, ACS_BLOCK);
            }
            else
            {
                mvaddch(i, j, ' ');
            }
        }
    }
}

void randomize_board(gol &gol, std::uint32_t seed)
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

std::int64_t timestamp_ms()
{
    return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch())
        .count();
}

int main()
{
    initscr();
    noecho();
    curs_set(0);

    getmaxyx(stdscr, rows, cols);

    std::uint32_t seed = std::random_device{}();

    gol gol(20, 20);
    randomize_board(gol, seed);

    draw_tiles(gol);
    refresh();

    while (gol.tick())
    {
        draw_tiles(gol);
        refresh();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    endwin();

    printf("Dimensions     : %dx%d\n", gol.height(), gol.width());
    printf("Seed           : 0x%X\n", seed);
    printf("Generations    : %d\n", gol.total_generations());
    printf("Ending State   : %d\n", gol.end_state());
    printf("Stable Periods : %d\n", gol.stable_period().value_or(0));

    return 0;
}
