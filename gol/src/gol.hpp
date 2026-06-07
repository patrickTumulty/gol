
#ifndef GOL_HPP
#define GOL_HPP

#include <optional>
#include <vector>

#define IN_BOUNDS_INC(V, LOWER, UPPER) ((V) >= (LOWER) && (V) <= (UPPER))

template <typename T> class mat
{
  public:
    mat(int height, int width, T initialValue) : _height(height), _width(width)
    {
        for (int i = 0; i < height; i++)
        {
            _mat.push_back(std::vector<T>(_width, initialValue));
        }
    }

    ~mat() = default;
    mat(const mat<T> &other)
    {
        _width = other._width;
        _height = other._height;
        for (int i = 0; i < _height; i++)
        {
            _mat.push_back(std::vector<T>(other._mat[i]));
        }
    }

    int height()
    {
        return _height;
    }

    int width()
    {
        return _width;
    }

    std::optional<T> get_cell(int x, int y) const
    {
        if (!IN_BOUNDS_INC(x, 0, _width - 1) || !IN_BOUNDS_INC(y, 0, _height - 1))
        {
            return {};
        }
        return _mat[y][x];
    }

    void set_cell(int x, int y, T value)
    {
        if (!IN_BOUNDS_INC(x, 0, _width - 1) || !IN_BOUNDS_INC(y, 0, _height - 1))
        {
            return;
        }
        _mat[y][x] = value;
    }

  private:
    int _height;
    int _width;
    std::vector<std::vector<T>> _mat;
};

void GolTick(mat<bool> &golMat);

#endif // GOL_HPP
