#define BOOST_TEST_MODULE Base::Initializer
#include <boost/test/unit_test.hpp>
using namespace boost::unit_test;

#include "base/game.hpp"

class Tester : public Game
{
  public:
    Tester() :Game{5, 5, 5} {}
};

BOOST_FIXTURE_TEST_SUITE(Base_Game, Tester)

BOOST_AUTO_TEST_CASE(test_click)
{
}

BOOST_AUTO_TEST_CASE(test_started)
{
}

BOOST_AUTO_TEST_SUITE_END()
