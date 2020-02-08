#include "case.hpp"

template <unsigned int LINE, unsigned int COLUMN>
class Grid
{
  public:
    Case& at(unsigned int line, unsigned int column)
    {
      return grid_[line][column];
    }

  private:
    Case grid_[LINE][COLUMN];
};

