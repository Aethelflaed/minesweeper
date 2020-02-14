#define BOOST_TEST_MODULE BASE_CASE
#include <boost/test/included/unit_test.hpp>
#include "base/case.hpp"

BOOST_AUTO_TEST_CASE(case_click)
{
  Case c;
  c.mine(false);
  BOOST_TEST(!c.click());

  c.mine(true);
  BOOST_TEST(c.click());

  c.flagged(true);
  BOOST_TEST(!c.click());
}
