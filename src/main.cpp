#include <iostream>
#include "base/grid.hpp"
#include "base/initializer.hpp"

int main() {
  Initializer::add<Initializer> ("default");

  Grid g{5, 5, 5};

  Initializer::make(g)->initialize();

  g.print();
  return 0;
}
