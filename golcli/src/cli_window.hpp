
#ifndef CLI_WINDOW_HPP
#define CLI_WINDOW_HPP

#include <ncurses.h>

struct cli_context
{
    int rows;
    int cols;
};

class cli_window
{
  public:
    cli_window(int height, int width);
    virtual ~cli_window();

    virtual void update(const cli_context ctx) = 0;
    virtual void window_resize(const cli_context ctx)
    {
    }

  protected:
    void center_window_horizontal(const cli_context ctx);
    void center_window_vertical(const cli_context ctx);
    void center_window(const cli_context ctx);

    WINDOW *_win;
    int _height;
    int _width;
    int _x = 0;
    int _y = 0;
};

#endif // CLI_WINDOW_HPP
