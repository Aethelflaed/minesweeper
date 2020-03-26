#include "base/initializer.hpp"

#include <random>

Initializer::Initializer(Grid& grid)
  :grid(grid)
{
}

void Initializer::operator() ()
{
  set_mines();
  fill_adjacent_mine_numbers();
}

void Initializer::set_mines()
{
  std::random_device rd;
  std::default_random_engine engine(rd());

  std::uniform_int_distribution<unsigned int> line_dist(0, grid.line() - 1);
  std::uniform_int_distribution<unsigned int> column_dist(0, grid.column() - 1);

  unsigned int mine_number = 0;

  while (mine_number < grid.mine_number())
  {
    unsigned int line = line_dist(engine);
    unsigned int column = column_dist(engine);

    Square& square = grid.at(line, column);

    if (! initialized(square))
    {
      square.mine(true);
      initialized(square, true);
      ++mine_number;
    }
  }
}

void Initializer::fill_adjacent_mine_numbers()
{
  for (unsigned int x = 0; x < grid.line(); ++x)
  {
    for (unsigned int y = 0; y < grid.column(); ++y)
    {
      Square& square = grid.at(x, y);
      if (! initialized(square))
      {
        square.adjacent_mine_number(adjacent_mine_number(x, y));
        initialized(square, true);
      }
    }
  }
}

unsigned int Initializer::adjacent_mine_number(unsigned int x, unsigned int y)
{
  return
    mine_top_left(x, y) +
    mine_top(x, y) +
    mine_top_right(x, y) +
    mine_left(x, y) +
    mine_right(x, y) +
    mine_bottom_left(x, y) +
    mine_bottom(x, y) +
    mine_bottom_right(x, y);
}

unsigned int Initializer::mine_top_left(unsigned int x, unsigned int y)
{
  if (x > 0)
  {
    if (y > 0)
    {
      return mine_to_number(x - 1, y - 1);
    }
  }

  return 0;
}

unsigned int Initializer::mine_top(unsigned int x, unsigned int y)
{
  if (x > 0)
  {
    return mine_to_number(x - 1, y);
  }

  return 0;
}

unsigned int Initializer::mine_top_right(unsigned int x, unsigned int y)
{
  if (x > 0)
  {
    if (y < grid.column() - 1)
    {
      return mine_to_number(x - 1, y + 1);
    }
  }

  return 0;
}

unsigned int Initializer::mine_left(unsigned int x, unsigned int y)
{
  if (y > 0)
  {
    return mine_to_number(x, y - 1);
  }

  return 0;
}

unsigned int Initializer::mine_right(unsigned int x, unsigned int y)
{
  if (y < grid.column() - 1)
  {
    return mine_to_number(x, y + 1);
  }

  return 0;
}

unsigned int Initializer::mine_bottom_left(unsigned int x, unsigned int y)
{
  if (x < grid.line() - 1)
  {
    if (y > 0)
    {
      return mine_to_number(x + 1, y - 1);
    }
  }

  return 0;
}

unsigned int Initializer::mine_bottom(unsigned int x, unsigned int y)
{
  if (x < grid.line() - 1)
  {
    return mine_to_number(x + 1, y);
  }

  return 0;
}

unsigned int Initializer::mine_bottom_right(unsigned int x, unsigned int y)
{
  if (x < grid.line() - 1)
  {
    if (y < grid.column() - 1)
    {
      return mine_to_number(x + 1, y + 1);
    }
  }

  return 0;
}

unsigned int Initializer::mine_to_number(unsigned int x, unsigned int y)
{
  // bool to int is totally legal in C++
  return grid.at(x, y).mine();
}

bool Initializer::initialized(const Square& square) const
{
  return square.initialized;
}

void Initializer::initialized(Square& square, bool value)
{
  square.initialized = value;
}
