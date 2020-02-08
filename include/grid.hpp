#include <vector>
#include "case.hpp"

class Grid
{
  public:
    Grid(unsigned int line, unsigned int column, unsigned int mine_number);

    void click(unsigned int line, unsigned int column);
    void toggle_flag(unsigned int line, unsigned int column);

    Case& at(unsigned int line, unsigned int column);

    unsigned int line() const;
    unsigned int column() const;
    unsigned int mine_number() const;
    unsigned int flag_number() const;

    bool failed() const;
    bool cleared() const;

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

