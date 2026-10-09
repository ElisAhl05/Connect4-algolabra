# Connect 4 Definition

Opinto-ohjelma: Tietojenkäsittelytiede (HY), kandidaatin tutkinto

As I am not sufficient enough in writing Finnish, the rest of the documentation and code will be in English. I am however good enough in English, Swedish and Finnish in order to give feedback on projects in any of these languages.

The project is an automatic Connect 4 playing AI, that can be played against using a console interface. Whenever the player inputs a move into the terminal, the AI will in one second make its own move, until either the player or the AI wins, when the game will restart.

Code will be created using C++, using standard libraries for data structures. For user interface, the user will be able to input positions into the terminal and will be shown a graphic representation of the board after every move.

Otherwise, I have a sufficient understanding of C, Python, Javascript and C# to evaluate projects done in these languages.

The board itself will consist of an array of array, that store any brick on the board. Using a min-max algorithm and a heuristic function, optimal moves will be generated for any position, leading to victory or stalling defeat. Using iterative deepening and ordered moves, the best move will be sought for as efficiently as possible. Using a hashed data-structure, previous best moves will be recorded, allowing for time saving as these will be tested first. A basic heuristic function will evaluate any position given. Alpha-beta pruning will be used to further effectivize the code.

The program recieves input in the form of a number 1-7. Using this, a connect-4 board is generated based on the previous moves. The above described will be applied on this board, finding the best move. The user is then fed back the board with this move played.

The core of the project is implementing iterative deepening and a min-max function that utilizes alpha-beta pruning in order to find good moves efficiently. This should be separated into clear functions with different purposes, one for controlling iterative deepening, one for executing the recursive min-max function and one for calculating the scores of positions.

## Sources
https://en.wikipedia.org/wiki/Minimax
https://en.wikipedia.org/wiki/Alpha-beta_pruning
https://en.wikipedia.org/wiki/Connect_Four
