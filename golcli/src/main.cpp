

#include "gol.hpp"
#include <clocale>
#include <cstdint>
#include <ncurses.h>
#include <ncursesw/ncurses.h>
#include <random>
#include <thread>

int alt = 0;
int cols = 0;
int rows = 0;

void drawTiles(gol &gol)
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

void randomizeBoard(gol &gol)
{
    // 1. Initialize a random device and the engine
    std::random_device rd;
    std::mt19937 gen(rd());

    // 2. Define a Bernoulli distribution (50% chance of true by default)
    std::bernoulli_distribution d(0.5);

    for (int i = 0; i < gol.height(); i++)
    {
        for (int j = 0; j < gol.width(); j++)
        {
            gol.set_cell(j, i, d(gen));
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

    gol gol(rows, cols);
    randomizeBoard(gol);

    drawTiles(gol);
    refresh();

    int frame = 0;
    float framerate = 15.0;
    int frameDeltaMS = (1.0f / framerate) * 1000;

    int counter = 0;

    while (gol.tick())
    {
        drawTiles(gol);
        refresh();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    endwin();

    printf("%d\n", gol.total_generations());

    return 0;
}
