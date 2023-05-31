/*
* Method file for 'NumberTile' class
* The class is the same as in 'numbers' project
* except for the following modifications:
*
* - 'print' method is removed
*   (no need for ASCII output)
*
* - 'set_value' method is added
*   (the method sets value for any tile object, unlike
*    'new_value' method)
*
*  - 'tile_value' method is added
*    (the method returns the value of the tile, and it is
*     used when displaying the gameboard in the GUI)
*
* Student: Tatu Anttila
* Student ID: 150227694
* Student e-mail: tatu.anttila@tuni.fi
* */

#include "numbertile.hh"
#include "gameboard.hh"
#include <iomanip>

Coords operator+(Coords lhs, Coords rhs)
{
    return std::make_pair(lhs.first + rhs.first, lhs.second + rhs.second);
}

NumberTile::NumberTile(int value, Coords coords, GameBoard* board):
    value_(value), coords_(coords), board_(board), is_merged_(false)
{
}

NumberTile::~NumberTile()
{
}

bool NumberTile::move(Coords direction, const int goal_val)
{
    Coords curr_loc = coords_;
    Coords new_loc = coords_ + direction;
    while( is_on_board( new_loc ) )
    {
        NumberTile* curr = board_->get_item(curr_loc);
        NumberTile* dest = board_->get_item(new_loc);
        if( dest->value_ == 0 )
        {
            dest->value_ = curr->value_;
            dest->is_merged_ = curr->is_merged_;
            curr->value_ = 0;
            curr->is_merged_ = false;
        }
        else if( dest->value_ == curr->value_ and
                 not dest->is_merged_ and
                 not curr->is_merged_ )
        {
            dest->value_ = 2 * curr->value_;
            curr->value_ = 0;
            dest->is_merged_ = true;
            return dest->value_ == goal_val;
        }
        curr_loc = new_loc;
        new_loc = dest->coords_ + direction;
    }
    return false;
}

bool NumberTile::new_value(int new_val)
{
    if( value_ == 0 )
    {
        value_ = new_val;
        return true;
    }
    return false;
}

void NumberTile::set_value(int new_val)
{
    value_= new_val;
}

bool NumberTile::is_empty()
{
    return value_ == 0;
}

void NumberTile::reset_turn()
{
    is_merged_ = false;
}

int NumberTile::tile_value()
{
    return value_;
}

bool NumberTile::is_on_board(Coords coords)
{
    return coords.first >= 0 and coords.first < SIZE and
           coords.second >= 0 and coords.second < SIZE;
}
