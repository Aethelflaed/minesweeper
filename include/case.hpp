#include <cstdint>

class Case
{
  public:
    /**
     * Set clicked to true and return mine() if not flagged()
     *
     * If flagged(), return false
     */
    bool click();

    /**
     * If not clicked(), return true if flagged() is changed to true.
     *
     * Otherwise, return false.
     */
    bool flag();

    /**
     * If not clicked(), return true if flagged() is changed to false.
     *
     * Otherwise, return false.
     */
    bool unflag();

    bool mine() const;
    void mine(bool mine);

    bool clicked() const;
    void clicked(bool clicked);

    bool flagged() const;
    void flagged(bool flagged);

    uint8_t adjacent_mines_number() const;
    void adjacent_mines_number(uint8_t number);

  private:
    bool mine_{false};
    bool clicked_{false};
    bool flagged_{false};
    uint8_t adjacent_mines_number_{0};
};
