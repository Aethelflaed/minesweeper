#ifndef BASE_INITIALIZER_HPP
#define BASE_INITIALIZER_HPP

#include "grid.hpp"

/**
 * Base class to initialize a Grid.
 *
 * Square is friend with this class, allowing to modify the internal data
 * structure.
 *
 * It is a class and not a function to enable inheritance, which permits to
 * keep the "friendship" benefit.
 *
 * Usage:
 *
 *  Initializer()(grid)
 */
class Initializer
{
  public:
    Initializer(Grid& grid);

    void operator() ();

  protected:
    /**
     * Set the mines on the grid, given the grid mine number.
     *
     * This method does NOT check if a mine has already been set on the game,
     * calling it in this case would result in an incorrect number of mines.
     */
    void set_mines();

    /**
     * Once the mines have been set, call this method to fill the adjacent
     * mine numbers on the remaining squares.
     */
    void fill_adjacent_mine_numbers();

    /**
     * Returns the number of mine adjacent to (x, y)
     */
    unsigned int adjacent_mine_number(unsigned int x, unsigned int y);

    /**
     * Returns 1 or 0 depending on if the square in the direction relative
     * to (x, y) has a mine or not.
     */
    unsigned int mine_top_left(unsigned int x, unsigned int y);
    unsigned int mine_top(unsigned int x, unsigned int y);
    unsigned int mine_top_right(unsigned int x, unsigned int y);
    unsigned int mine_left(unsigned int x, unsigned int y);
    unsigned int mine_right(unsigned int x, unsigned int y);
    unsigned int mine_bottom_left(unsigned int x, unsigned int y);
    unsigned int mine_bottom(unsigned int x, unsigned int y);
    unsigned int mine_bottom_right(unsigned int x, unsigned int y);

    /**
     * Returns 1 or 0 depending on if the square at (x, y) has a mine or not
     */
    unsigned int mine_to_number(unsigned int x, unsigned int y);

    /**
     * get/set the initialized field on the given square.
     */
    bool initialized(const Square& square) const;
    void initialized(Square& square, bool value);

    Grid& grid;
};

#endif // BASE_INITIALIZER_HPP
