#define BOOST_TEST_MODULE Base::Initializer
#include <boost/test/unit_test.hpp>
using namespace boost::unit_test;

#include "base/initializer.hpp"

class Tester : public Initializer
{
  public:
    Grid grid{5, 5, 5};

    Tester() :Initializer{grid} {}
    Tester(Grid& grid) :Initializer{grid} {}
};

BOOST_AUTO_TEST_CASE(test_factory)
{
  Grid grid{5, 5, 5};
  Initializer::add<Initializer>("default");
  Initializer::add<Tester>("test");

  auto init1 = Initializer::make(grid);
  auto init2 = Initializer::make(grid, "test");

  BOOST_CHECK(dynamic_cast<Initializer*>(init1.get()) != nullptr);
  BOOST_CHECK(dynamic_cast<Tester*>(init2.get()) != nullptr);

  BOOST_CHECK(Initializer::make(grid, "foo") == nullptr);
}

BOOST_FIXTURE_TEST_SUITE(Base_Initializer, Tester)

BOOST_AUTO_TEST_CASE(test_call)
{
  this->initialize();

  unsigned int mine_number = 0;

  for(unsigned int x = 0; x < 5; ++x)
  {
    for(unsigned int y = 0; y < 5; ++y)
    {
      if (grid.at(x, y).mine())
      {
        ++mine_number;
      }
      BOOST_TEST(initialized(grid.at(x, y)));
    }
  }

  BOOST_CHECK_EQUAL(5U, mine_number);
}

BOOST_AUTO_TEST_CASE(test_fill_adjacent_mine_numbers)
{
  grid.at(0, 0).mine(true);
  grid.at(2, 2).mine(true);
  grid.at(4, 3).mine(true);

  fill_adjacent_mine_numbers();

  unsigned int expected[5][5] = {
    {0, 1, 0, 0, 0},
    {1, 2, 1, 1, 0},
    {0, 1, 0, 1, 0},
    {0, 1, 2, 2, 1},
    {0, 0, 1, 0, 1}
  };

  for(unsigned int x = 0; x < 5; ++x)
  {
    for(unsigned int y = 0; y < 5; ++y)
    {
      BOOST_CHECK_EQUAL(expected[x][y],
          grid.at(x, y).adjacent_mine_number());
    }
  }
}

BOOST_AUTO_TEST_CASE(test_adjacent_mine_number)
{
  grid.at(0, 0).mine(true);
  grid.at(1, 0).mine(true);
  grid.at(1, 1).mine(true);
  grid.at(1, 2).mine(true);

  BOOST_CHECK_EQUAL(4U, adjacent_mine_number(0, 1));
  BOOST_CHECK_EQUAL(2U, adjacent_mine_number(0, 2));
  BOOST_CHECK_EQUAL(1U, adjacent_mine_number(0, 3));
  BOOST_CHECK_EQUAL(0U, adjacent_mine_number(0, 4));

  BOOST_CHECK_EQUAL(2U, adjacent_mine_number(2, 0));
  BOOST_CHECK_EQUAL(3U, adjacent_mine_number(2, 1));
  BOOST_CHECK_EQUAL(2U, adjacent_mine_number(2, 2));
  BOOST_CHECK_EQUAL(1U, adjacent_mine_number(2, 3));
  BOOST_CHECK_EQUAL(0U, adjacent_mine_number(2, 4));
}

BOOST_AUTO_TEST_CASE(test_mine_top_left)
{
  grid.at(0, 0).mine(true);

  BOOST_CHECK_EQUAL(0U, mine_top_left(0, 0));
  BOOST_CHECK_EQUAL(0U, mine_top_left(0, 1));
  BOOST_CHECK_EQUAL(0U, mine_top_left(1, 0));
  BOOST_CHECK_EQUAL(1U, mine_top_left(1, 1));
}

BOOST_AUTO_TEST_CASE(test_mine_top)
{
  grid.at(0, 0).mine(true);

  BOOST_CHECK_EQUAL(0U, mine_top(0, 0));
  BOOST_CHECK_EQUAL(0U, mine_top(0, 1));
  BOOST_CHECK_EQUAL(1U, mine_top(1, 0));
  BOOST_CHECK_EQUAL(0U, mine_top(1, 1));
}

BOOST_AUTO_TEST_CASE(test_mine_top_right)
{
  grid.at(0, 4).mine(true);

  BOOST_CHECK_EQUAL(0U, mine_top_right(0, 4));
  BOOST_CHECK_EQUAL(0U, mine_top_right(0, 3));
  BOOST_CHECK_EQUAL(0U, mine_top_right(1, 4));
  BOOST_CHECK_EQUAL(1U, mine_top_right(1, 3));
}

BOOST_AUTO_TEST_CASE(test_mine_left)
{
  grid.at(0, 0).mine(true);

  BOOST_CHECK_EQUAL(0U, mine_left(0, 0));
  BOOST_CHECK_EQUAL(1U, mine_left(0, 1));
  BOOST_CHECK_EQUAL(0U, mine_left(1, 0));
  BOOST_CHECK_EQUAL(0U, mine_left(1, 1));
}

BOOST_AUTO_TEST_CASE(test_mine_right)
{
  grid.at(0, 4).mine(true);

  BOOST_CHECK_EQUAL(0U, mine_right(0, 4));
  BOOST_CHECK_EQUAL(1U, mine_right(0, 3));
  BOOST_CHECK_EQUAL(0U, mine_right(1, 4));
  BOOST_CHECK_EQUAL(0U, mine_right(1, 3));
}

BOOST_AUTO_TEST_CASE(test_mine_bottom_left)
{
  grid.at(4, 0).mine(true);

  BOOST_CHECK_EQUAL(0U, mine_bottom_left(4, 0));
  BOOST_CHECK_EQUAL(0U, mine_bottom_left(4, 1));
  BOOST_CHECK_EQUAL(0U, mine_bottom_left(3, 0));
  BOOST_CHECK_EQUAL(1U, mine_bottom_left(3, 1));
}

BOOST_AUTO_TEST_CASE(test_mine_bottom)
{
  grid.at(4, 0).mine(true);

  BOOST_CHECK_EQUAL(0U, mine_bottom(4, 0));
  BOOST_CHECK_EQUAL(0U, mine_bottom(4, 1));
  BOOST_CHECK_EQUAL(1U, mine_bottom(3, 0));
  BOOST_CHECK_EQUAL(0U, mine_bottom(3, 1));
}

BOOST_AUTO_TEST_CASE(test_mine_bottom_right)
{
  grid.at(4, 4).mine(true);

  BOOST_CHECK_EQUAL(0U, mine_bottom_right(4, 4));
  BOOST_CHECK_EQUAL(0U, mine_bottom_right(4, 3));
  BOOST_CHECK_EQUAL(0U, mine_bottom_right(3, 4));
  BOOST_CHECK_EQUAL(1U, mine_bottom_right(3, 3));
}

BOOST_AUTO_TEST_SUITE_END()
