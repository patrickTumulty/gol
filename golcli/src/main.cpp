

#include "ascii_title.hpp"
#include "gol.hpp"
#include "gol_randomizer.hpp"
#include <clocale>
#include <cstdint>
#include <cstdio>
#include <iostream>
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

// int main()
// {
//     initscr();
//     noecho();
//     curs_set(0);
//
//     getmaxyx(stdscr, rows, cols);
//
//     std::uint32_t seed = std::random_device{}();
//
//     gol gol(rows, cols);
//     randomize_gol_board(gol, seed);
//
//     draw_tiles(gol);
//     refresh();
//
//     while (gol.tick())
//     {
//         draw_tiles(gol);
//         refresh();
//         std::this_thread::sleep_for(std::chrono::milliseconds(100));
//     }
//
//     endwin();
//
//     printf("Dimensions     : %dx%d\n", gol.height(), gol.width());
//     printf("Seed           : 0x%X\n", seed);
//     printf("Generations    : %d\n", gol.total_generations());
//     printf("Ending State   : %d\n", gol.end_state());
//     printf("Stable Periods : %d\n", gol.stable_period().value_or(0));
//
//     return 0;
// }

#include <ncurses.h>
#include <string>
#include <vector>

void print_ascii(WINDOW *win, const std::string &text, int start_y, int start_x)
{
    int y = start_y;
    int x = start_x;

    std::string line;

    for (char c : text)
    {
        if (c == '\n')
        {
            mvwprintw(win, y++, x, "%s", line.c_str());
            line.clear();
        }
        else
        {
            line.push_back(c);
        }
    }

    if (!line.empty())
        mvwprintw(win, y, x, "%s", line.c_str());
}

int main()
{
    std::vector<std::string> items = {"Start Game", "Load Game", "Settings", "Credits", "Exit"};

    int selected = 0;

    initscr();
    noecho();
    cbreak();
    keypad(stdscr, TRUE);
    curs_set(0);

    int rows, cols;
    getmaxyx(stdscr, rows, cols);

    clear();
    refresh();

    int title_offset = (cols / 2) - (97 / 2);
    WINDOW *title_win = newwin(17, 97, 0, title_offset);

    WINDOW *options_win = newwin(10, 30, 0, 20);

    while (true)
    {
        clear();

        int start_row = (rows - (int)items.size()) / 2;

        mvwprintw(options_win, 1, 1, "Main Menu");

        for (int i = 0; i < (int)items.size(); ++i)
        {
            int x = (cols - items[i].size()) / 2;
            int y = start_row + i;

            if (i == selected)
            {
                attron(A_REVERSE);
                mvprintw(y, x, "%s", items[i].c_str());
                attroff(A_REVERSE);
            }
            else
            {
                mvprintw(y, x, "%s", items[i].c_str());
            }
        }

        wrefresh(options_win);

        int ch = getch();

        switch (ch)
        {
        case KEY_UP:
            selected = (selected == 0) ? items.size() - 1 : selected - 1;
            break;

        case KEY_DOWN:
            selected = (selected == (int)items.size() - 1) ? 0 : selected + 1;
            break;

        case 10: // Enter
            endwin();
            printf("Selected: %s\n", items[selected].c_str());
            return 0;
        }

        wrefresh(options_win);

        // print_ascii(title_win, ASCII_GAME_OF_LIFE_TITLE, 1, 1);
        // wrefresh(title_win);
        //
        // refresh();
    }

    delwin(title_win);
    delwin(options_win);

    endwin();
}
