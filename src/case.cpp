#include "case.hpp"

Case::Case(bool mine)
  :mine_{mine}
{
}

bool Case::mine() const
{
  return this->mine_;
}

bool Case::clicked() const
{
  return this->clicked_;
}

void Case::clicked(bool clicked)
{
  this->clicked_ = clicked;
}

bool Case::flagged() const
{
  return this->flagged_;
}

void Case::flagged(bool flagged)
{
  this->flagged_ = flagged;
}

uint8_t Case::adjacent_mines_number() const
{
  return this->adjacent_mines_number_;
}

void Case::adjacent_mines_number(uint8_t number)
{
  this->adjacent_mines_number_ = number;
}
