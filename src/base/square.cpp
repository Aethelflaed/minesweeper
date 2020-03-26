#include "base/square.hpp"

bool Square::click()
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

bool Square::flag()
{
  if (this->clicked_ || this->flagged_)
  {
    return false;
  }
  this->flagged(true);
  return true;
}

bool Square::unflag()
{
  if (this->clicked_ || !this->flagged_)
  {
    return false;
  }
  this->flagged(false);
  return true;
}

bool Square::mine() const
{
  return this->mine_;
}

void Square::mine(bool mine)
{
  if (!this->initialized)
  {
    this->mine_ = mine;
  }
}

bool Square::clicked() const
{
  return this->clicked_;
}

void Square::clicked(bool clicked)
{
  this->clicked_ = clicked;
}

bool Square::flagged() const
{
  return this->flagged_;
}

void Square::flagged(bool flagged)
{
  this->flagged_ = flagged;
}

uint8_t Square::adjacent_mine_number() const
{
  return this->adjacent_mine_number_;
}

void Square::adjacent_mine_number(uint8_t number)
{
  if (!this->initialized)
  {
    this->adjacent_mine_number_ = number;
  }
}
