#define BOOST_TEST_MODULE BASE_GRID
#include <boost/test/included/unit_test.hpp>
#include "base/grid.hpp"

BOOST_AUTO_TEST_CASE(grid_click)
{
  Grid g{5, 5, 5};
  BOOST_TEST(g.cleared());
}
