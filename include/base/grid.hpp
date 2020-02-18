#include <vector>
#include "case.hpp"

class Grid
{
  public:
    /**
     * Construct a new Grid with given parameters but does not populate the squares
     * with mines and numbers.
     */
    Grid(unsigned int line, unsigned int column, unsigned int mine_number);

    /**
     * Click on square designated by {line, column} and if the square is:
     *
     *  flagged: do nothing
     *
     *  a mine: set the grid to failed
     *
     *  already cleared without number: do nothing
     *
     *  already cleared with number: try to chord
     *
     *  not cleared: clear the square, and clear the region if it has no number
     */
    void click(unsigned int line, unsigned int column);

    /**
     * Set or unset the flag on the square designated by {line, column},
     * if possible
     */
    void toggle_flag(unsigned int line, unsigned int column);

    /**
     * Returns a reference to the square designated by {line, column}
     */
    Case& at(unsigned int line, unsigned int column);

    unsigned int line() const;
    unsigned int column() const;
    unsigned int mine_number() const;
    unsigned int flag_number() const;

    bool failed() const;
    bool cleared() const;

    void print() const;

  private:
    void flag(unsigned int line, unsigned int column);
    void unflag(unsigned int line, unsigned int column);

    unsigned int line_;
    unsigned int column_;
    unsigned int mine_number_;

    std::vector<std::vector<Case>> grid_;

    bool failed_{false};
    unsigned int clear_case_number_{0};
    unsigned int cleared_case_number_{0};
    unsigned int flag_number_{0};
};

