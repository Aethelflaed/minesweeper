#include "base/case.hpp"

bool Case::click()
{
  if (this->flagged_)
  {
    return false;
  }
  else
  {
    this->clicked(true);
    return this->mine();
  }
}

bool Case::flag()
{
  if (this->clicked_ || this->flagged_)
  {
    return false;
  }
  this->flagged(true);
  return true;
}

bool Case::unflag()
{
  if (this->clicked_ || !this->flagged_)
  {
    return false;
  }
  this->flagged(false);
  return true;
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

uint8_t Case::adjacent_mine_number() const
{
  return this->adjacent_mine_number_;
}

void Case::adjacent_mine_number(uint8_t number)
{
  this->adjacent_mine_number_ = number;
}
