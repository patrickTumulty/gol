

#include "ascii_title.hpp"
#include "cli_window.hpp"
#include "gol.hpp"
#include "gol_randomizer.hpp"
#include "options_window.hpp"
#include <chrono>
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

const option_item OPTION_NEW_GAME(0, "New Game");
const option_item OPTION_REPLAY(1, "Replay");
const option_item OPTION_EXIT(2, "Exit");

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

namespace
{
option_window option_win(10, 30);
std::optional<option_item> selected;
}; // namespace

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

void run_update_loop()
{
    initscr();
    noecho();
    cbreak();
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    curs_set(0);

    clear();
    refresh();

    cli_context ctx{0};

    while (true)
    {
        getmaxyx(stdscr, ctx.rows, ctx.cols);

        int ch = getch();
        if (ch == KEY_RESIZE)
        {
            // endwin();
            // refresh();
            // clear();
            //
            // option_win.window_resize(ctx);
        }

        // werase(title_win);
        // print_ascii(title_win, ASCII_GAME_OF_LIFE_TITLE, 1, 1);
        // wrefresh(title_win);

        option_win.update(ctx);
        selected = option_win.get_selected_item();
        if (selected.has_value())
        {
            printf("Selected: %s\n", selected.value().name.c_str());
            break;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(33));
    }

    endwin();
}

int main()
{
    // int title_offset = (cols / 2) - (97 / 2);
    // WINDOW *title_win = newwin(17, 97, 2, title_offset);

    // int options_offset = (cols / 2) - (30 / 2);
    // WINDOW *options_win = newwin(10, 30, 20, options_offset);
    // mvwprintw(options_win, 1, 1, "Main Menu");

    option_win.add_option(OPTION_NEW_GAME);
    option_win.add_option(OPTION_REPLAY);
    option_win.add_option(OPTION_EXIT);

    run_update_loop();

    printf("Selected: %s\n", selected.value_or(OPTION_EXIT).name.c_str());
}
