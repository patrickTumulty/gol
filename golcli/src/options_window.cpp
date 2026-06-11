
#include "options_window.hpp"
#include "cli_window.hpp"
#include <ncurses.h>

option_window::option_window(int height, int width) : cli_window(height, width), _items()
{
    nodelay(_win, true);
    keypad(_win, true);
}

void option_window::add_option(const option_item item)
{
    _items.push_back(item);
}

std::optional<option_item> option_window::get_selected_item()
{
    return _selected;
}

void option_window::window_resize(const cli_context ctx)
{
    center_window(ctx);
    clearok(_win, true);
}

void option_window::update(const cli_context ctx)
{
    werase(_win);
    box(_win, 0, 0);
    mvwprintw(_win, 1, 1, "Options:");
    mvwhline(_win, 2, 1, ACS_HLINE, _width - 2);

    for (int i = 0; i < (int)_items.size(); ++i)
    {
        int y = i + 3;

        if (i == _selected_index)
        {
            wattron(_win, A_REVERSE);
            mvwprintw(_win, y, 1, "* %-26s", _items[i].name.c_str());
            wattroff(_win, A_REVERSE);
        }
        else
        {
            mvwprintw(_win, y, 1, "* %-26s", _items[i].name.c_str());
        }
    }

    wrefresh(_win);

    int ch = wgetch(_win);
    if (ch == ERR)
    {
        // No input available right now (non-blocking behavior)
        // You can do background processing/animations here
        napms(10); // Sleep 10ms to prevent 100% CPU usage
        return;
    }

    switch (ch)
    {
    case KEY_UP:
        _selected_index = (_selected_index == 0) ? _items.size() - 1 : _selected_index - 1;
        break;
    case KEY_DOWN:
        _selected_index = (_selected_index == (int)_items.size() - 1) ? 0 : _selected_index + 1;
        break;
    case 10: // Enter
        _selected = _items[_selected_index];
        break;
    }
}
