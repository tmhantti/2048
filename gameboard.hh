/*
* Header file for 'GameBoard' class
*
* The class is the same as in 'numbers' project
* except for the following modifications:
*
* 1) 'print' method is removed.
*    (no need for ASCII output)
*
* 2) Original 'fill' method is split into two methods:
*    - 'fill_init' (for initializing structure of GameBoard object)
*    - 'fill_values' (for initializing contents of GameBoard object)
*
* 3) 'get_tile_value' method is added.
*     The method returns value of a NumberTile object
*     contained in a GameBoard object.
*     It is used when displaying the gameboard in the GUI.
*
* Student: Tatu Anttila
* Student ID: 150227694
* Student e-mail: tatu.anttila@tuni.fi
* */

#ifndef GAMEBOARD_HH
#define GAMEBOARD_HH

#include "numbertile.hh"
#include <vector>
#include <random>

const int SIZE = 4;
const int NEW_VALUE = 2;

class GameBoard
{
public:
    // Constructor
    GameBoard();

    // Destructor
    ~GameBoard();

    // Initializes Gameboard object with nullptrs.
    void init_empty();

    // initialize structure of GameBoard object:
    void fill_init();

    // initialize contents of GameBoard object:
    void fill_values(int seed);

    // Draws a new location (coordinates) from the random number generator and
    // puts the NEW_VALUE on that location, unless check_if_empty is true and
    // the gameboard is full.
    void new_value(bool check_if_empty = true);

    // Returns true, if all the tiles in the game board are occupied,
    // otherwise returns false.
    bool is_full() const;

    // Moves the number tiles in the gameboard, if possible (by calling
    // move method for each number tile).
    // Finally, resets turn of all number tiles.
    bool move(Coords dir, int goal);

    // Returns the element (number tile) in the given coordinates.
    NumberTile* get_item(Coords coords);

    // Returns the value of the element (number tile)
    // in the given coordinates.
    int get_tile_value(Coords coords);

private:
    // Internal structure of the game board
    std::vector<std::vector<NumberTile*>> board_;

    // Random number generator and distribution,
    // they work better, if they are attributes of a class.
    std::default_random_engine randomEng_;
    std::uniform_int_distribution<int> distribution_;
};

#endif // GAMEBOARD_HH
