# Connect4
Course project: Connect 4 solver

Code is compiled using CMake. In order to run the code, please navigate to the project folder in a Linux system and write the lines

`make`

`./main`

Nothing more is needed. Upon writing these lines, the project will start running in the console. Instructions are given there as well. The player can input columns 1-7 to play them on the board, upon which the AI runs iterative deepening for one second and responds with a move of its own. This is repeated until either player has won, when the game resets. The player may also input "u" to undo a move and jump back to the last time it was his turn. The functionality is very basic, and other inputs are not allowed.

As the project starts, the tests are run and the results outputted to the screen, which the player might want to take a look at.
