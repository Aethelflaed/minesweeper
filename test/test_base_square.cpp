#define BOOST_TEST_MODULE Base::Square
#include <boost/test/unit_test.hpp>
#include "base/square.hpp"

BOOST_AUTO_TEST_CASE(default_constructible)
{
  BOOST_TEST(std::is_default_constructible<Square>::value);
}

BOOST_AUTO_TEST_CASE(click)
{
  Square c;

  c.mine(false);
  BOOST_TEST(!c.click());
  BOOST_TEST(c.clicked());

  c.mine(true);
  BOOST_TEST(c.click());

  c.flagged(true);
  BOOST_TEST(!c.click());
}

BOOST_AUTO_TEST_CASE(flag)
{
  Square c;

  BOOST_TEST(c.flag());
  BOOST_TEST(!c.flag());

  c.flagged(false);
  c.clicked(true);

  BOOST_TEST(!c.flag());
  BOOST_TEST(!c.flagged());
}

BOOST_AUTO_TEST_CASE(unflag)
{
  Square c;
  c.flagged(true);

  BOOST_TEST(c.unflag());
  BOOST_TEST(!c.unflag());

  c.flagged(true);
  c.clicked(true);

  BOOST_TEST(!c.unflag());
  BOOST_TEST(c.flagged());
}
