#ifndef BASE_GAME_HPP
#define BASE_GAME_HPP

#include <chrono>

#include "grid.hpp"
#include "initializer.hpp"

/**
 * Represents a game of minesweeper, including:
 * - the grid
 * - a timer which starts on the first click
 * - a click count
 */
class Game
{
  public:
    using time_point = std::chrono::system_clock::time_point;
    using duration_t = std::chrono::duration<double>;

    /**
     * Constructs a Game and the underlying grid
     */
    Game(unsigned int line, unsigned int column, unsigned int mine_number);

    /**
     * Delegates to grid and counts clicks
     *
     * Returns true if the game is finished, i.e. either `failed()` or `cleared()`
     *
     * Starts the game if not started.
     *
     * Does nothing if the game is finished and return true.
     */
    bool click(unsigned int line, unsigned int column);

    /**
     * Delegates to grid and counts clicks
     *
     * Returns the number of flags on the grid
     *
     * Starts the game if not started.
     *
     * Does nothing if the game is finished and return 0.
     */
    unsigned int toggle_flag(unsigned int line, unsigned int column);

    bool started() const;

    bool failed() const;
    bool cleared() const;

    time_point start() const;
    duration_t duration() const;

    Grid& grid();
    const Grid& grid() const;

    unsigned int click_count() const;

  private:
    void start_if_not_started();

    Grid grid_;

    unsigned int click_count_{0};

    time_point start_;
    time_point end_;
};

#endif // BASE_GAME_HPP
