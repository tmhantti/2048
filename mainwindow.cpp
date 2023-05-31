/* Method file for 'MainWindow' class.
 *
 * Detailed descriptions are given on comments below
 * and also on the beginning of 'mainwindow.hh' file.
 *
 * Student: Tatu Anttila
 * Student ID: 150227694
 * Student e-mail: tatu.anttila@tuni.fi
 *
 */

#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include "gameboard.hh"

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QLabel>
#include <QString>
#include <QKeyEvent>
#include <cmath>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Initialize GameBoard object:
    initBoard();

    // Configure main layout of the gameboard:
    initGBLayout();

    // * Additional feature: *
    // Initialize QGraphicsView widget used for displaying
    // the GUI background color:
    initBGcolour();

    // Draw gridlines for the gameboard:
    drawBackground();

    // Initialize data structure (2D vector containg QLabel objects).
    // This is used to display numbers for each square of the gameboard:
    initLabelVector();

    // Initialize QLabel objects which show numbers
    // (or blanks) in each square of the gameboard:
    initLabels();

    // Set minimum and maximum values for the
    // 'spinBox' widget that is used for setting the goal value:
    ui->goalSpinBox->setMinimum(2);
    ui->goalSpinBox->setMaximum(SIZE*SIZE);

    // initially, 'Reset' button is disabled:
    ui->resetButton->setEnabled(false);

    // display initial message in the GUI status box:
    ui->statusBox->setText(welcomeMsg);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// Configure main layout of the gameboard:
void MainWindow::initGBLayout()
{
    // Variables related to the location and size of the gameboard:
    int borderDown = SIZE*GRID_SIDE;
    int borderRight = SIZE*GRID_SIDE;

    // The graphicsView object is placed on the window
    // at the following coordinates:
    // The width of the graphicsView is borderRight added by 2,
    // since the borders take one pixel on each side
    // (1 on the left, and 1 on the right).
    // Similarly, the height of the graphicsView is borderDown added by 2.

    scene_ = new QGraphicsScene(this);

    ui->graphicsView->setGeometry(LEFT_MARGIN, TOP_MARGIN,
                                  borderRight+2, borderDown+2);

    ui->graphicsView->setScene(scene_);

    scene_->setSceneRect(0, 0, borderRight, borderDown);
}

// Initialize GameBoard object:
void MainWindow::initBoard()
{
    board.init_empty();
    board.fill_init();
}

// Set up initial state of the board
void MainWindow::initBoardState()
{
    // set the RNG seed value:
    seed_= ui->seedSpinBox->value();

    // set the goal value:
    goal_=  pow(2, ui->goalSpinBox->value());

    // initialize values of the gameboard:
    board.fill_values(seed_);

    // display the numbers in the gameboard:
    setLabels();
}

// Draw grid lines for the gameboard
void MainWindow::drawBackground()
{
    // specify thickness of grid borders:
    QPen outlinePen(Qt::black);
    outlinePen.setWidth(BORDER_WIDTH);

    for (int row = 0; row < SIZE; row++)
    {
        for (int column = 0; column < SIZE; column++)
        {
            scene_->addRect(column * GRID_SIDE, row * GRID_SIDE,
                            GRID_SIDE, GRID_SIDE,
                            outlinePen);
        }
    }
}

// Initialize 2D vector ('numbers' structure) containing
// QLabel object for each square in the gameboard:
void MainWindow::initLabelVector()
{
    std::vector<QLabel*> rowVector= {};

    for (int row = 0; row < SIZE; row++) {
        rowVector.push_back(nullptr);
    }

    for (int column = 0; column < SIZE; column++) {
        numbers_.push_back(rowVector);
    }

}

// Initializes QLabel widgets which show the numbers
// (or blank if the square value is 0)
// of each square in the gameboard:
void MainWindow::initLabels()
{
    for (int row = 0; row < SIZE; row++)
        {
        for (int column = 0; column < SIZE; column++)
            {
            QLabel* newLabel= new QLabel(this);

            // place labels according to the margins and grid box size:
            newLabel->setAlignment(Qt::AlignCenter| Qt::AlignCenter);
            newLabel->setGeometry(QRect(LEFT_MARGIN + column * GRID_SIDE,
                                        TOP_MARGIN + row * GRID_SIDE,
                                        GRID_SIDE, GRID_SIDE));

            numbers_.at(row).at(column) = newLabel;

            // initially, set label text content as blank:
            numbers_.at(row).at(column) ->setText("");
            }
        }
}

// Displays the numbers on the GUI gameboard:
//
// * Additional feature (included in the method): *
//   calculates the sum of tile values over the gameboard
//   and displays the score on QLabel widget 'scoreDisplay'

void MainWindow::setLabels()
{
    // game score:
    score_= 0;

    // value of a gameboard tile:
    int tileValue;

    // the following QString variable is used for
    // displaying the number on a gameboard square
    // (if number >0, otherwise the variable is set as empty):
    QString labelText;

    for (int row = 0; row < SIZE; row++)
        {
        for (int column = 0; column < SIZE; column++)
            {
            Coords currCoords = {row, column};
            tileValue= board.get_tile_value(currCoords);

            if (tileValue== 0)
                labelText= "";
            else
                labelText= QString::number(tileValue);

            // update value displayed in the the current label:
            numbers_.at(row).at(column)->setText(labelText);

            // update the font of the current label:
            setLabelFont(row, column, tileValue);

            // update score points:
            score_+= tileValue;
        }
    }
    // update the score displayed on GUI:
    ui->scoreDisplay->setText(QString::number(score_));
}

// modify font of the text displayed in the label
// (according to the tile value (variable tileValue)):
void MainWindow::setLabelFont(const int &row,
                              const int &column,
                              const int &tileValue)
{
    // These variables are used for setting up
    // the stylesheet for the label:
    QString fontFormat= "";
    QString fontColor;
    int colorIndex;

    // Finds the correct index value of 'FONT_COLOURS' vector
    // based on the tile value.

    // Maximum tile value used in choosing the index value
    // (tiles with larger values are set to the same color -
    //  for basic game setup, this value is 2048):

    int numberOfColours= FONT_COLOURS.size();

    int maxColorValue=
            pow(2, (numberOfColours - 2));

    if (tileValue > 0 && tileValue <= maxColorValue)
        colorIndex= int(log2(tileValue));

    else if (tileValue > maxColorValue)
        colorIndex= ( numberOfColours - 1);

    else
        colorIndex = 0;

    fontColor= FONT_COLOURS[colorIndex];

    fontFormat.append(QString("QLabel { font-size: %1pt; color: %2;} ").
                      arg(FONT_SIZE, fontColor));

    numbers_.at(row).at(column)->setStyleSheet (fontFormat);
}


// checks the keyboard input:
void MainWindow::keyReleaseEvent(QKeyEvent *e)
{
    Coords dir = DEFAULT_DIR;

    switch ( e->key() )
       {
       case Qt::Key_W:
           dir = UP; break;
       case Qt::Key_A:
           dir = LEFT; break;
       case Qt::Key_S:
           dir = DOWN; break;
       case Qt::Key_D:
           dir = RIGHT; break;
       }

    // if relevant key is pressed and game state is active,
    // update the GUI gameboard accordingly:
    if ( dir != DEFAULT_DIR && readyFlag_ )
        updateBoard(dir);
}

// Update the GUI gameboard after player has made a move,
// check also win and lose conditions:
void MainWindow::updateBoard(const Coords &dir)
{
    // check if the player has reached the goal value:
    if( board.move(dir, goal_) )
    {
        // update the background colour of GUI:
        setBGcolour("G");

        // update message displayed in the status box of GUI:
        ui->statusBox->setText(winMsg1 + QString::number(goal_) + winMsg2);

        // ignore keyboard commands until user starts another game:
        readyFlag_ = false;

        setLabels();

        return;
    }

    // check if the board is full:
    else if( board.is_full() )
    {
        // update the background colour of GUI:
        setBGcolour("R");

        // update message displayed in the status box of GUI:
        ui->statusBox->setText(loseMsg);

        // ignore keyboard commands until user starts another game:
        readyFlag_ = false;

        setLabels();

        return;
    }
    board.new_value(false);
    setLabels();
}

// Activates when 'Start' button is clicked:
void MainWindow::on_startButton_clicked()
{
    initBoardState();

    // reset button is activated:
    ui->resetButton->setEnabled(true);
    // start button is deactivated:
    ui->startButton->setEnabled(false);

    // spin boxes are deactivated:
    ui->seedSpinBox->setEnabled(false);
    ui->goalSpinBox->setEnabled(false);

    // keyboard presses are now accounted for:
    readyFlag_ = true;

    // update message displayed in the status box of GUI:
    ui->statusBox->setText(playMsg1 + playMsg2 +
                           QString::number(goal_) + "."  );
}

// Resets the game state:
void MainWindow::on_resetButton_clicked()
{
    initBoardState();

    // start button is activated:
    ui->startButton->setEnabled(true);
    // reset button is disabled:
    ui->resetButton->setEnabled(false);

    // spin boxes are activated:
    ui->seedSpinBox->setEnabled(true);
    ui->goalSpinBox->setEnabled(true);

    // ignore keyboard presses until user starts another game:
    readyFlag_ = false;

    // update message displayed in the status box of GUI:
    ui->statusBox->setText(welcomeMsg);

    // updare the background color of the GUI:
    setBGcolour("W");
}

// Initialize QGraphicsScene_ widget
// which is used for changing GUI background colour:
void MainWindow::initBGcolour()
{
    BGscene_ = new QGraphicsScene(this);
    ui->BGView->setScene(BGscene_);
}

// Change the background colour of GUI:
void MainWindow::setBGcolour(const QString &col)
{
    if (col == "W")
        ui-> BGView ->
                setStyleSheet("QGraphicsView#BGView {background-color:white}");
    if (col == "R")
        ui-> BGView ->
                setStyleSheet("QGraphicsView#BGView {background-color:red}");
    if (col == "G")
        ui-> BGView ->
                setStyleSheet("QGraphicsView#BGView {background-color:green}");
}




