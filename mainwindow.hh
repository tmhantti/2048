/* Header file for 'MainWindow' class
 *
 * This class takes care of the GUI aspect of the game.
 *
 * The following methods are used to implement basic features of the GUI:
 * (constants and variables are described below along with the code)
 *
 * Methods for the basic features:
 *
 * - drawBackground : Draw grid lines on the gameboard
 *      (see also mainwindow.cpp for more details)
 *
 * - initLabelVector : Set up internal structure for 'numbers' structure
 *      ( 2D vector containing QTlabels in (row,column) coordinates) ).
 *
 * - initLabels : Initialize QTlabels for each square in the gameboard.
 *
 * - initBoard :  Initialize GameBoard object used in GUI.
 *
 * - initBoardState : Set up initial configuration of the GUI gameboard.
 *
 * - initGBLayout : Initialize GUI layout.
 *
 * - setLabels : Display numbers for each square on the GUI gameboard.
 *
 * - updateBoard : Update state of the game board as a response
 *      to the user input (relevant key presses).
 *
 * - on_startButton_clicked : QT Creator Slot, related to the GUI
 *      (see also mainwindow.ui).
 *
 * - on_resetButton_clicked : QT Creator Slot, related to the GUI
 *      (see also mainwindow.ui).
 *
 * - keyReleaseEvent : Checks for the user's keyboard input.
 *
 * * Methods related to the implemented extra features: *
 *
 * - initBGcolour : Initialize QGraphicsView widget used for displaying
 *                  the GUI background colour.
 *
 * - setBGcolour : changes the GUI background colour according to
 *                 the state of game
 *
 * - setLabelFont : sets the font size (this is specified with the QString
 *                  constant FONT_SIZE, see below)
 *                  and font colour of the text labels displaying the
 *                  number in each tile.

 * Student: Tatu Anttila
 * Student ID: 150227694
 * Student e-mail: tatu.anttila@tuni.fi
 * */

#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include "numbertile.hh"
#include "gameboard.hh"

#include <QMainWindow>
#include <QPushButton>
#include <QTextBrowser>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QLabel>
#include <QKeyEvent>
#include <QString>
#include <vector>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    // GameBoard object:
    GameBoard board;

    // QGraphicsScene object for the gameboard layout:
    QGraphicsScene* scene_;

    // 2D vector containg QLabel objects which
    // are used to display the number
    // in each square of the gameboard:
    std::vector<std::vector<QLabel*>> numbers_;

    // Seed value for the RNG:
    int seed_ = 0;

    // Target value of the game:
    int goal_ = SIZE;

    // Flag for checking if user has clicked 'start' button
    // (this is used to check keyboard input:
    //  keyboard presses are ignored until the game has been started):
    bool readyFlag_ = false;

    // Length of the side of an individual square in the gameboard:
    const int GRID_SIDE= 80;

    // The margins for placing the gameboard on the GUI window:
    const int LEFT_MARGIN = 10; // x coordinate
    const int TOP_MARGIN = 260; // y coordinate

    // Thickness of the borders of the GUI gameboard tiles:
    const int BORDER_WIDTH= 2;

    // Messages displayed in the status box of GUI:
    const QString welcomeMsg= "After setting seed and goal values, "
                         "click 'Start' button to start the game. ";

    const QString playMsg1= "Use 'wasd' keys to move the tiles.\n"
                        "Tiles with the same number merge into "
                        "one when they touch.\n"
                        "Add them up to reach the goal value! \n";
    const QString playMsg2= "The goal value is: ";

    const QString loseMsg= "Can't add new tile, you lost!\n"
                           "Click 'Reset' button to play again.";

    const QString winMsg1= "You reached the goal value of ";
    const QString winMsg2= ", congratulations!\n"
                           "Click 'Reset' button to play again.";

    // These constants are used to specify the "direction"
    // of a gameboard move that user makes during a game:

    const Coords DEFAULT_DIR = {0, 0};
    const Coords LEFT = {0, -1};
    const Coords UP = {-1, 0};
    const Coords RIGHT = {0, 1};
    const Coords DOWN = {1, 0};

    // * Objects, variables and constants related
    //  to the additional features: *

    // Widget used for displaying the background colour of GUI:
    QGraphicsScene* BGscene_ ;

    // Game score (calculated as a sum of tile values over gameboard):
    int score_= 4 * NEW_VALUE;

    // Font size for numbers displayed in the GUI gameboard:
    const QString FONT_SIZE= "24";

    // Font colour specifications which correspond to different tile values
    // (up to a tile value of 2048: for large values, only a single colour
    //  is used):
    const std::vector<QString> FONT_COLOURS = {
        "white",        // 0
        "gray",         // 2
        "darkGray",     // 4
        "magenta",      // 8
        "darkMagenta",  // 16
        "cyan",         // 32
        "darkCyan",     // 64
        "blue",         // 128
        "darkBlue",     // 256
        "green",        // 512
        "red",          // 1024
        "yellow",       // 2048
        "black",        // > 2048
    };

    // Methods for basic implementation of the game:

    // Draw grid lines for the gameboard:
    void drawBackground();

    // Set up internal structure for 'numbers' object
    // ( 2D vector containing QTlabels in (row,column) coordinates ):
    void initLabelVector();

    // Initialization method for the gameboard labels (QTLabel objects)
    // (the labels show numbers / blank for each square in the gameboard):
    void initLabels();

    // Display numbers on the GUI gameboard:
    void setLabels();

    // Initialize GameBoard object used in GUI:
    void initBoard();

    // Set up the initial configuration of the GUI gameboard:
    void initBoardState();

    // Initialize GUI gameboard layout:
    void initGBLayout();

    // Update state of the GUI gameboard:
    void updateBoard(const Coords &dir);

    // ** Methods related to additional features: **

    // Initializes BGscene_ object
    // (used for displaying background colour of GUI):
    void initBGcolour();

    // Method for changing the background colour of GUI:
    void setBGcolour(const QString &col);

    // Changes the font of the text according to
    // the value of a gameboard tile:
    void setLabelFont(const int &row, const int &column,
                      const int &tileValue);

protected:
    // handles output via keyboard events:
    void keyReleaseEvent(QKeyEvent* event);

private slots:
    void on_startButton_clicked();
    void on_resetButton_clicked();
};
#endif // MAINWINDOW_HH
