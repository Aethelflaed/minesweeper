#ifndef BASE_INITIALIZER_HPP
#define BASE_INITIALIZER_HPP

#include <unordered_map>
#include <memory>
#include <functional>

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
 * Basic usage:
 *
 * ```cpp
 * Initializer(grid).initialize();
 * ```
 *
 * ALternatively, Initializer is also a factory:
 *
 * ```cpp
 * // register different types
 * Initializer::add<Initializer>("defaut");
 * Initializer::add<AnotherInitializer>("another");
 *
 * // make without name defaults to "default"
 * Initializer::make(grid);
 * Initializer::make(grid, "another");
 * ```
 */
class Initializer
{
  public:
    Initializer(Grid& grid);

    virtual void initialize();

    /**
     * Initializer::add<Initializer>("default");
     *
     * Will register the template type as an initializer associated with the given name.
     */
#if defined(__cpp_concepts) && __cpp_concepts >= 201507
    /**
     * This versions works with concepts, a C++20 feature which provides better
     * diagnostic messages, such as:
     *
     * > error: no matching function for call to ‘Initializer::add<Grid>(const char [8])’
     * > note:   constraints not satisfied
     * > note: ‘is_base_of_v<Initializer, T>’ evaluated to false
     * > note: ‘is_convertible_v<T*, Initializer*>’ evaluated to false
     */
    template<class T>
      requires (std::is_base_of_v<Initializer, T> && std::is_convertible_v<T*, Initializer*>)
    static void add(const std::string& name)
    {
      initializers.insert_or_assign(name,
          // we cast to the desired type to select the correct overload,
          // which is needed otherwise we don't know which one is wanted.
          static_cast<std::unique_ptr<T> (*) (Grid&)> (std::make_unique<T>) );
    }
#else
    /**
     * This version works without concepts, but on substitution error will issue message such as:
     *
     * > error: no matching function for call to ‘Initializer::add<Grid>(const char [8])’
     * > error: no type named ‘type’ in ‘struct std::enable_if<false, void>’
     */
    template<class T,
      typename = std::enable_if_t<std::is_base_of_v<Initializer, T>>
      >
    static void add(const std::string& name)
    {
      initializers.insert_or_assign(name, static_cast<std::unique_ptr<T> (*) (Grid&)>(std::make_unique<T>) );
    }
#endif

    /**
     * Make a new Initializer, using the "default" name.
     */
    static std::unique_ptr<Initializer> make(Grid& grid);
    /**
     * Make a new Initializer, using the given name.
     */
    static std::unique_ptr<Initializer> make(Grid& grid, const std::string& name);

  protected:
    static std::unordered_map<std::string, std::function<std::unique_ptr<Initializer>(Grid&)>> initializers;

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
