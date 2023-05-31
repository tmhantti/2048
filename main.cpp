/* Description of the game implemented in the coding project 'numbers_gui':
*
* This program generates a game of 2048, a tile combining game
* where the goal is to get from 2's to 2^N where N is an integer
* (player can specify the number N within certain limits)
* The board is SIZE x SIZE (original was 4 x 4) and every round
* the player chooses a direction to which the tiles should fall.
* If the tiles collide with a wall or a different value,
* they will move as close as they can get. If they collide with
* a tile with same value, they will combine and double the value. The
* tile will continue to move and combine until a wall or other tile
* comes along. This means there's some recursion, see NumberTile::move().
* Game will end when the value of 'goal' variable is reached
* (game won) or new tile can't be added to the board (game lost).
*
* This implementation is based on the C++ project 'numbers' template but
* it contains GUI for the game along with some extra features.
*
* Furher comments regarding the code are provided at the beginning
* of each code file contained in the project.
*
* Student: Tatu Anttila
* Student ID: 150227694
* Student e-mail: tatu.anttila@tuni.fi
* */

#include "mainwindow.hh"
#include "numbertile.hh"
#include "gameboard.hh"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
