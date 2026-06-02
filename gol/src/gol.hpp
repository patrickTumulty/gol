
#ifndef GOL_HPP
#define GOL_HPP

#include <vector>

class BoolMat
{
  public:
    BoolMat(int height, int width);
    ~BoolMat();

    BoolMat(const BoolMat &other);

    int GetHeight() const;
    int GetWidth() const;

    bool GetCell(int x, int y) const;
    void SetCell(int x, int y, bool value);

  private:
    int _height;
    int _width;
    std::vector<std::vector<bool>> _mat;
};

void GolTick(BoolMat &golMat);

#endif // GOL_HPP
