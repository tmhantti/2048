Student project for course 'Programming 2' (Tampere University, 2022). 
Application done using C++/Qt. 

* Rules of the game: 

 This program generates a game of 2048, a tile combining game
 where the goal is to get from 2's to 2^N where N is an integer
 (player can specify the number N within certain limits)
 The board is SIZE x SIZE (original was 4 x 4) and every round
 the player chooses a direction (by 'wasd' keys of keyboard)
 to which the tiles should fall. 
 
 If the tiles collide with a wall or a different value,
 they will move as close as they can get. If they collide with
 a tile with same value, they will combine and double the value. The
 tile will continue to move and combine until a wall or other tile
 comes along. 

 Game will end when the value of the goal variable is reached
 (game won) or new tile can't be added to the board (game lost).

* Overview: 

The project consists of the following files:

- gameboard.cpp / gameboard.hh :

  These are modified versions of the corresponding 
  files taken from the 'numbers' template.
  See comments at the beginning of the header file for details. 

- numbertile.cpp / numbertile.hh :

  Some changes were made to the original templates.   
  See comments at the beginning of the header file for details. 

- mainwindow.cpp / mainwindow.hh / mainwindow.ui :
  
  (see below for GUI descriptiom)

* GUI implementation: 

  Layout was done (to some extent) directly using QTcreator 
  (via manipulating directly "mainwindow.ui"). To display the gameboard 
  and its state, however, some explicit coding was added to 
  'mainwindow.hh' / 'mainwindow.cpp' 
  (see comments at the beginning of the files).  

* GUI description

 - player can choose seed value for random number generator (RNG),
   via 'spinBox' widget displayed on the GUI.

 - player can choose target value for the game
   (as in choosing N where 2^N is the goal value for a game)
   via 'spinBox' widget displayed on the GUI. 

 - 'Start', 'Reset' and 'Close' buttons are included in the GUI. 
    Initial values for seed and goal value choices are shown on 'spinBox'
    the corresponding widgets. After player clicks 'Start' button, 
    he/she can make moves via keyboard presses (see below) or he/she can click 
    'Reset' button to start a new game during a game. 

    After winning or losing the game, player can start a new game 
    by clicking 'Reset' button. This allows for changing goal/seed values 
    and to start a new game by clicking 'Start' button. 

    'Close' button can be clicked at any time, this will close the GUI window
    and exits the game.
    
 - Status box is included in the GUI (QTextBrowser widget): 
   this shows messages according to the current state of gameplay,
   including messages for indicating if player has won or lost the game.

 - Gameboard shown in the GUI was implemented using QT creator with some coding 
   (mainly using 'QGraphicsScene', 'QGraphicsView' and 'QLabel' classes)
    
 - 'wasd' keys are used for gameplay input. Measures were taken to ignore
    keyboard inputs when the keyboard presses would mess up functionality
    with some GUI widgets (i.e. certain widgets are disabled / enabled 
    according to the gameplay state).  

*  Extra features:

 - Background colour of GUI changes according to the state of the game. 
   This was done by adding QGraphicsView/ QGraphicsScene elements.  
   QGraphicsView widget 'BGView' is set to the the same size 
   as the original QWindow size. This widget is 'Send to back' of 
   QMainWindow. However, 'BGView' does not scale with the GUI window size. 
   Hence this only a partial solution. 

 - Game score is displayed on GUI via QLabel 'scoreDisplay'. 
   The score is calculated by summing up tile values over the gameboard. 

 - non-GUI feature: The game goal value is a power of 2 (by design, see above). 

 - Colors of the tile numbers in game board are changed according to the tile value.
   This done by introducing a vector specifying the colors (constant 'FONT_COLOURS') 
   and adding a method ('setLabelFont') which changes the color of the 
   of the text displayed in the label.  


