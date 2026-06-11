
#ifndef OPTIONS_WINDOW_HPP
#define OPTIONS_WINDOW_HPP

#include "cli_window.hpp"
#include <optional>
#include <string>
#include <vector>

struct option_item
{
    std::string name;
    int id;

    option_item(int id, std::string name) : id(id), name(name)
    {
    }
};

class option_window : public cli_window
{
  public:
    option_window(int height, int width);
    ~option_window() = default;

    void update(const cli_context ctx) override;

    void window_resize(const cli_context ctx) override;

    void add_option(const option_item item);

    std::optional<option_item> get_selected_item();

  private:
    std::vector<option_item> _items;
    std::optional<option_item> _selected;
    int _selected_index = 0;
};

#endif // OPTIONS_WINDOW_HPP
