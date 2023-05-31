/*
* Header file for 'NumberTile' class
*
* The class is the same as in the 'numbers' project
* except for the following modifications:
*
* 1) 'print' method is removed
*    (no need for ASCII output)
*
* 2) 'set_value' method is added
*    (this method sets value for any tile object, unlike
*     'new_value' method)
*
* 3) 'tile_value' method is added
*    (the method returns the value of the tile, and it is
*     used for displaying the gameboard in the GUI)
*
* Student: Tatu Anttila
* Student ID: 150227694
* Student e-mail: tatu.anttila@tuni.fi
* */

#ifndef NUMBERTILE_HH
#define NUMBERTILE_HH

#include <vector>

using Coords = std::pair<int, int>;

// Forward declaration, to avoid circular include's
class GameBoard;

class NumberTile
{
public:
    // Constructor
    NumberTile(int value, Coords coords, GameBoard* board);

    // Destructor
    ~NumberTile();   

    // Moves the number tile in the given direction and merges it, if possible.
    // Returns true, if the player won the game, i.e. if the goal value was
    // reached, otherwise returns false.
    bool move(Coords direction, int goal_val);

    // Sets a new value for an empty number tile.
    // Returns true, if a new value was set, otherwise returns false.
    bool new_value(int new_val);

    // Returns true, if the number tile is empty, i.e. if it has the value 0.
    bool is_empty();

    // Sets the value of is_merged_ as false.
    void reset_turn();

    // Sets a new value for any tile:
    void set_value(int new_val);

    // Returns the value of the tile:
    int tile_value();

private:

    // Value in the number tile
    int value_;

    // Coordinates of the number tile
    Coords coords_;

    // Pointer to the gameboard, where the number tile lies
    GameBoard* board_;

    // Tells if the number is merged or not,
    // can be true only temporarily during moves
    bool is_merged_;

    // Returns true, if the given coordinates are on the gameboard,
    // otherwise returns false.
    bool is_on_board(Coords coords);
};

#endif // NUMBERTILE_HH
