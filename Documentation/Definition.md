# Connect 4 Definition

Opinto-ohjelma: Tietojenkäsittelytiede (HY), kandidaatin tutkinto

As I am not sufficient enough in writing Finnish, the rest of the documentation and code will be in English. I am however good enough in English, Swedish and Finnish in order to give feedback on projects in any of these languages.

The project is an optimal move finder for Connect 4, which can be tested by the user using the terminal.

Code will be created using C++. For user interface, the user will be able to input positions into the terminal and will be shown a graphic representation of the board after every move.

Otherwise, I have a sufficient understanding of C, Python, Javascript and C# to evaluate projects done in these languages.

The board itself will consist of an array of stacks, to which bricks are added. Using a min-max algorithm and a heuristic function, optimal moves will be generated for any position, leading to victory or stalling defeat. Using iterative deepening and ordered moves, the best move will be sought for as efficiently as possible. Using a hashed data-structure, previous best moves will be recorded, allowing for time saving. A basic heuristic function will evaluate any position given.

The program recieves input in the form of a number 1-7. Using this, a connect-4 board is generated based on the previous moves. The above described will be applied on this board, finding the best move. The user is then fed back the board with this move played.

As the project is quite complicated, it is not possible to supply timing requirements at this point, before having started the project. The heuristic function will optimally be O(1).

The core of the project is the algorithm itself that will find the best move. The method for doing this has been described above. The project will utilize alpha-beta pruning in order to find good moves faster.

## Sources
https://en.wikipedia.org/wiki/Minimax
https://en.wikipedia.org/wiki/Alpha-beta_pruning
https://en.wikipedia.org/wiki/Connect_Four
