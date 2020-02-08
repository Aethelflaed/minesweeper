#include "case.hpp"

bool Case::click()
{
  if (this->flagged)
  {
    return false;
  }
  else
  {
    this->clicked(true);
    return this->mine();
  }
}

void Case::flag()
{
  if (!this->clicked)
  {
    this->flagged(true);
  }
}

bool Case::mine() const
{
  return this->mine_;
}

void Case::mine(bool mine)
{
  this->mine_ = mine;
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
