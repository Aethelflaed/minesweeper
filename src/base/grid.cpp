#include <iostream>
#include "base/grid.hpp"

Grid::Grid(unsigned int line, unsigned int column, unsigned int mine_number) :
  line_{line},
  column_{column},
  mine_number_{mine_number},
  grid_{line, std::vector<Square>{column}},
  clear_square_number_{line * column - mine_number}
{
}

void Grid::click(unsigned int line, unsigned int column)
{
  Square& square = at(line, column);
  if (square.click())
  {
    this->failed_ = true;
  }
  else
  {
    ++this->cleared_square_number_;
    if (square.adjacent_mine_number() == 0)
    {
      /* TODO: clear region */
    }
  }
}

void Grid::toggle_flag(unsigned int line, unsigned int column)
{
  Square& square = at(line, column);
  if (square.flagged())
  {
    unflag(line, column);
  }
  else
  {
    flag(line, column);
  }
}

void Grid::flag(unsigned int line, unsigned int column)
{
  Square& square = at(line, column);
  if (square.flag())
  {
    ++this->flag_number_;
  }
}

void Grid::unflag(unsigned int line, unsigned int column)
{
  Square& square = at(line, column);
  if (square.unflag())
  {
    --this->flag_number_;
  }
}

Square& Grid::at(unsigned int line, unsigned int column)
{
  return grid_[line][column];
}

unsigned int Grid::line() const
{
	return this->line_;
}

unsigned int Grid::column() const
{
	return this->column_;
}

unsigned int Grid::mine_number() const
{
	return this->mine_number_;
}

unsigned int Grid::flag_number() const
{
  return this->flag_number_;
}

bool Grid::finished() const
{
  return this->failed_ ||
    clear_square_number_ == cleared_square_number_;
}

bool Grid::failed() const
{
	return this->failed_;
}

bool Grid::cleared() const
{
	return failed_ != true &&
    clear_square_number_ == cleared_square_number_;
}

void Grid::print() const
{
  for(const auto& line : grid_)
  {
    for(const auto& square : line)
    {
      std::cout << square.mine();
      if (square.clicked())
      {
        std::cout << 'C';
      }
      else if(square.flagged())
      {
        std::cout << 'F';
      }
      else
      {
        std::cout << 'U';
      }
      std::cout << +square.adjacent_mine_number() << "  ";
    }
    std::cout << std::endl;
  }
}

