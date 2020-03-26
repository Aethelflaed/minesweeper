#include <iostream>
#include "base/grid.hpp"
#include "base/initializer.hpp"

int main() {
  Grid g{5, 5, 5};
  Initializer{g}();

  g.print();
  return 0;
}
