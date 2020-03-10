#include <iostream>
#include "base/grid.hpp"

Grid::Grid(unsigned int line, unsigned int column, unsigned int mine_number) :
  line_{line},
  column_{column},
  mine_number_{mine_number},
  grid_{line, std::vector<Case>{column}},
  clear_case_number_{line * column - mine_number}
{
}

void Grid::click(unsigned int line, unsigned int column)
{
  Case& case_ = at(line, column);
  if (case_.click())
  {
    this->failed_ = true;
  }
  else
  {
    ++this->cleared_case_number_;
    if (case_.adjacent_mine_number() == 0)
    {
      /* TODO: clear region */
    }
  }
}

void Grid::toggle_flag(unsigned int line, unsigned int column)
{
  throw "Not Implemented";
}

void Grid::flag(unsigned int line, unsigned int column)
{
  Case& case_ = at(line, column);
  if (case_.flag())
  {
    ++this->flag_number_;
  }
}

void Grid::unflag(unsigned int line, unsigned int column)
{
  Case& case_ = at(line, column);
  if (case_.unflag())
  {
    --this->flag_number_;
  }
}

Case& Grid::at(unsigned int line, unsigned int column)
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

bool Grid::failed() const
{
	return this->failed_;
}

bool Grid::cleared() const
{
	return this->clear_case_number_ == this->cleared_case_number_;
}

void Grid::print() const
{
  for(const auto& line : grid_)
  {
    for(const auto& case_ : line)
    {
      std::cout << case_.mine();
      if (case_.clicked())
      {
        std::cout << 'C';
      }
      else if(case_.flagged())
      {
        std::cout << 'F';
      }
      else
      {
        std::cout << 'U';
      }
      std::cout << +case_.adjacent_mine_number()
        << "  ";
    }
    std::cout << std::endl;
  }
}

