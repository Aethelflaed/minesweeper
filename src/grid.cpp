#include "grid.hpp"

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
  if (at(line, column).click())
  {
    this->failed_ = true;
  }
  else
  {
    ++this->cleared_case_number_;
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


bool Grid::failed() const
{
	return this->failed_;
}

bool Grid::cleared() const
{
	return this->clear_case_number_ == this->cleared_case_number_;
}

