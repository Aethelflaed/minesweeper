#include "base/game.hpp"
#include "base/initializer.hpp"

Game::Game(unsigned int line, unsigned int column, unsigned int mine_number)
  :grid_{line, column, mine_number}
{
  Initializer{grid_}();
}

bool Game::click(unsigned int line, unsigned int column)
{
  start_if_not_started();

  grid_.click(line, column);

  ++click_count_;

  if (grid_.failed())
  {
    end_ = std::chrono::system_clock::now();
    return true;
  }
  else if (grid_.cleared())
  {
    cleared_ = true;
    end_ = std::chrono::system_clock::now();
    return true;
  }

  return false;
}

unsigned int Game::toggle_flag(unsigned int line, unsigned int column)
{
  start_if_not_started();

  grid_.toggle_flag(line, column);

  ++click_count_;

  return grid_.flag_number();
}

bool Game::started() const
{
  return start_.time_since_epoch() == duration_t::zero();
}

bool Game::failed() const
{
  return cleared_ == false &&
    end_.time_since_epoch() == duration_t::zero();
}

bool Game::cleared() const
{
  return cleared_;
}

Game::time_point Game::start() const
{
  return start_;
}

Game::duration_t Game::duration() const
{
  return end_ - start_;
}

Grid& Game::grid()
{
  // reuse the const getter
  return
    // cast the return value to `Grid&` (drop the const qualifier)
    const_cast<Grid&>(
        // cast `this` to `const Game*` to call the const version
        const_cast<const Game*>(this)->grid()
        );
}

const Grid& Game::grid() const
{
  return grid_;
}

unsigned int Game::click_count() const
{
  return click_count_;
}

void Game::start_if_not_started()
{
  if (!started())
  {
    start_ = std::chrono::system_clock::now();
  }
}

