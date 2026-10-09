# Project execution

The project consists of several parts. The connect4.cpp-file is responsible for the user interface, and implements the classes and functions defined in the GameController.hpp header file in order to show a playable game to the user. There is also a separate testing folder, completely independent of the rest of the code, that is responsible for performing tests on the functions in the header file. The folder consists of a boards.hpp header, containing functions for converting moves into boards as well as boards and values that are used for the tests. The Testing.hpp header applies this functionality to perform tests.

## The header file (GameController.hpp)
The header file is the part that contains the core of the project. In this, two classes are defined. There is a Board class that represents Connect 4 boards with basic functionality like adding and removing pieces. There is also a function for recieving a printable version of the board, and a hashing function to convert the board into a hash value based of the contents.
This Board class is used by the other Gamecontroller class, that is able to calculate heuristic values on a board, hosts a min-max function, checking whether moves result in wins and further functions for allowing for iterative deepening.

## The implementation file (connect4.cpp)
This file contains a main() function that runs when the project is executed. Upon start, the tests are executed, and then a welcome message is shown. The function then runs a loop, at the start of which the current board is shown. When the player inputs a move, it is made on the board, and the iterative deepening function then run on the board to generate the AI's move. If "u" is input, the board will revert back to the last player move. There is also functionality for checking for columns not on the board, but a wrong formatted input can right now crash the project. The functions checks using the controllers win check function whether either the opponent or player has won. If the game is over, a message is shown and the board reset.

## The board testing file (boards.hpp)
This file contains a function that is able to convert a vector of moves (given as integers) into the board that results from making these moves. This function is very useful. Other than that, this file contains boards upon which tests can be run, along with the expected values of these tests and other relevant information for running the tests. This makes the actual testing cleaner, as the tests that are implement are stored elsewhere.

## The implemented testing file (Testing.hpp)
This file contains several things. In the start is an asserting function, that is responsible for outputting to the console whether a test succeeded. This is useful for knowing which test actually failed, if any.
Other than that, there are several functions for testing different functionalities of the main header file, such as the heuristic values and the min-max function. These functions return a value based of whether the test succeeded or not. The boards corresponding to the tests are gone through and the appropriate function run on these boards, then asserted that the result is the one expected. At the start of each test is outputted to the console which test is being done, useful for identifying which test is made.
The user is supposed to used the testAll function, that runs all the tests and returns whether they failed or not.

Right now, I have a hard time finding improvements for the project. The code is a bit cluttered in the main header file, I will admit, but should be clear enough. The tests could be implemented in such a way that they are only run when the user wants to. The main improvements would be on the UI: there could be ways of resetting the board mid-play, switching the player, modes for allowing the AI to play against itself, changing the time the AI uses etc. These are however functionalities that are not strictly neccessary for the underlying code. There might be ways of further effectivizing the code, reducing costly branching in the min-max algorithm, but the code is already very efficient. At the start of the game it can run 10+ iterations within one seconds, which only gets higher as the game goes on.

Large language models have not been crucial for the project. Visual studio has an automatic line completer that helps writing faster and making editing code easier, but this has had little effect on the project. Github also uses one for automatic commit message generation, that I have sometimes used. I also looked up using Mistral how Alpha-beta pruning worked in practice as I found the wikipedia page unclear, having it explain what exactly the method does.

The sources that I have used are really just the ones given in the definition document, mainly wikipedia articles. At different points I have consulted Stack Overflow and similar sites to lookup C++ standard library functionality and such problems.
https://en.wikipedia.org/wiki/Minimax
https://en.wikipedia.org/wiki/Alpha-beta_pruning
https://en.wikipedia.org/wiki/Connect_Four
