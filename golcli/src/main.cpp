

#include "gol.hpp"
#include <clocale>
#include <ncurses.h>
#include <ncursesw/ncurses.h>
#include <random>
#include <thread>

int alt = 0;
int cols = 0;
int rows = 0;

void drawTiles(mat<bool> &gol)
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

void randomizeBoard(mat<bool> &gol)
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

int main()
{
    initscr();
    noecho();
    curs_set(0);

    getmaxyx(stdscr, rows, cols);

    mat<bool> gol(rows, cols, false);
    randomizeBoard(gol);

    drawTiles(gol);
    refresh();

    int frame = 0;
    float framerate = 15.0;
    int frameDeltaMS = (1.0f / framerate) * 1000;

    int counter = 0;

    while (true)
    {
        GolTick(gol);
        drawTiles(gol);
        refresh();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    endwin();

    return 0;
}
