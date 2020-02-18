#define BOOST_TEST_MODULE Base::Grid
#include <boost/test/unit_test.hpp>
#include "base/grid.hpp"

BOOST_AUTO_TEST_CASE(click)
{
  Grid g{5, 5, 5};

  g.click(1, 1);
  BOOST_TEST(g.at(1, 1).clicked());

  g.at(1, 2).mine(true);
  g.click(1, 2);
  BOOST_TEST(g.failed());
}

BOOST_AUTO_TEST_CASE(toggle_flag)
{
  Grid g{5, 5, 5};

  // flag
  g.toggle_flag(1, 1);
  BOOST_TEST(g.at(1, 1).flagged());

  // unflag
  g.toggle_flag(1, 1);
  BOOST_TEST(!g.at(1, 1).flagged());

  // try to flag a clicked case
  g.click(1, 2);
  g.toggle_flag(1, 2);
  BOOST_TEST(!g.at(1, 1).flagged());
}
