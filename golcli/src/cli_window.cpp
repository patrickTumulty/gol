
#include "cli_window.hpp"
#include <ncurses.h>

cli_window::cli_window(int height, int width) : _height(height), _width(width), _win(newwin(height, width, 0, 0))
{
}

cli_window::~cli_window()
{
    delwin(_win);
}

void cli_window::center_window_horizontal(const cli_context ctx)
{
    int x_offset = (ctx.cols / 2) - (_width / 2);
    mvwin(_win, _y, x_offset);
    _x = x_offset;
}

void cli_window::center_window_vertical(const cli_context ctx)
{
    int y_offset = (ctx.rows / 2) - (_height / 2);
    mvwin(_win, y_offset, _x);
    _y = y_offset;
}

void cli_window::center_window(const cli_context ctx)
{
    int y_offset = (ctx.rows / 2) - (_height / 2);
    int x_offset = (ctx.cols / 2) - (_width / 2);
    mvwin(_win, y_offset, x_offset);
    _y = y_offset;
    _x = x_offset;
}
