

#include "gol.hpp"
#include "gol_randomizer.hpp"
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

    gol gol(rows, cols);
    randomize_gol_board(gol, seed);

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
