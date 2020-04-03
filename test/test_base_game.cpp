#define BOOST_TEST_MODULE Base::Initializer
#include <boost/test/unit_test.hpp>
using namespace boost::unit_test;

#include "base/game.hpp"

class Tester : public Game
{
  public:
    Tester() :Game{5, 5, 5} {}
};

class GameTestInitializer : public Initializer
{
  public:
    GameTestInitializer(Grid& grid) :Initializer{grid} {}

    void initialize() override
    {
      // do nothing
    }

    void set_mine(unsigned int line, unsigned int column)
    {
      grid.at(line, column).mine(true);
      initialized(grid.at(line, column), true);
    }
};

struct Config
{
  public:
    Config()
    {
      Initializer::add<GameTestInitializer>("default");
    }
};

BOOST_GLOBAL_FIXTURE(Config);

BOOST_FIXTURE_TEST_SUITE(s, Tester)

BOOST_AUTO_TEST_CASE(test_click_failure)
{
  BOOST_CHECK(! started());

  BOOST_CHECK(click(0, 0) == false);

  BOOST_CHECK(started());
  BOOST_CHECK(click_count() == 1);

  GameTestInitializer(grid()).set_mine(0, 0);

  BOOST_CHECK(click(0, 0) == true);
  BOOST_CHECK(failed());

  BOOST_CHECK(click_count() == 2);

  BOOST_CHECK(click(0, 0));
}

BOOST_AUTO_TEST_CASE(test_click_cleared)
{
  // to be tested later, once a clear region is set.
  BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(test_toggle_flag)
{
  BOOST_CHECK(! started());

  BOOST_CHECK(toggle_flag(0, 0) == 1);

  BOOST_CHECK(started());

  BOOST_CHECK(toggle_flag(0, 0) == 0);

  BOOST_CHECK(click_count() == 2);
}

BOOST_AUTO_TEST_SUITE_END()
