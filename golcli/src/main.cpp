

#include <ncurses.h>

int main()
{
    initscr();
    noecho();
    curs_set(0);

    int rows, cols;
    getmaxyx(stdscr, rows, cols);

    const char *msg = "Hello, World!";
    mvprintw(rows / 2, (cols - 13) / 2, "%s", msg);

    refresh();
    getch();

    endwin();
    return 0;
}
