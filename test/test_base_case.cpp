#define BOOST_TEST_MODULE Base::Case
#include <boost/test/unit_test.hpp>
#include "base/case.hpp"

BOOST_AUTO_TEST_CASE(default_constructible)
{
  BOOST_TEST(std::is_default_constructible<Case>::value);
}

BOOST_AUTO_TEST_CASE(click)
{
  Case c;

  c.mine(false);
  BOOST_TEST(!c.click());

  c.mine(true);
  BOOST_TEST(c.click());

  c.flagged(true);
  BOOST_TEST(!c.click());
}

BOOST_AUTO_TEST_CASE(flag)
{
  Case c;

  BOOST_TEST(c.flag());
  BOOST_TEST(!c.flag());

  c.flagged(false);
  c.clicked(true);

  BOOST_TEST(!c.flag());
  BOOST_TEST(!c.flagged());
}

BOOST_AUTO_TEST_CASE(unflag)
{
  Case c;
  c.flagged(true);

  BOOST_TEST(c.unflag());
  BOOST_TEST(!c.unflag());

  c.flagged(true);
  c.clicked(true);

  BOOST_TEST(!c.unflag());
  BOOST_TEST(c.flagged());
}
