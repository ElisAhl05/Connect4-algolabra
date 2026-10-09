# Testing report

The testing functionality, as described in the execution document, is contained within the testing folder of the project.

The following tests are done:
- Heuristic testing
- Win check testing
- Loss avoidance testing
- Win-in-one finding testing
- Find closest win testing
- Legal move testing

They are all implemented slightly differently from each other. In each test, five different hand-picked boards are tested, and if any result is invalid, the entire testing fails. Every test asserts that the resulting value is the same as the pre-calculated one.

### Heuristic testing
For this test, I have hand-picked five different boards at different states of the game. Each board is from a different game and are very different from each other, in order to make sure that the function runs correctly. As the chance of the AI "by mistake" finding the correct value should be very small, the function only checks whether the heuristic value is the same as the precalculated one. For each board, I have by hand gone through and counted all the two-in-a-rows and three-in-a-rows, sometimes through a very tideous process, and using this calculated what the heuristic value should be. The heuristic value has been calculated separately for each player. The board is then inputted to the game controllers evalutation function in order to find the values it assigns each possition, which is then compared to the precalculated one. The boards have been picked from games where I have played against the AI as well as ones where I have played against myself, in order to improve representability and variety.

### Win check testing
For this test, I have selected another five different hand-picked boards, three of which containing a four-in-a-row and two that do not. The function forms these boards and compares the value returned by the game controller's win check function to the value that I have manually assigned each position. The boards are of different complexity in order to have varied tests. The boards contains wins of both players.

### Loss avoidance testing
For this test, I have picked five boards where the opponent in the next move will be able to play a move that instantly wins the game, but where the player can play a move blocking this from happening. The boards picked are of different complexity, but all fulfill the same criterium. For each board, I have denoted which move the player can play in order to avoid instantly losing. The min-max function is run on the board using a depth of 2 (player: first depth, opponent: second), and checked that the function returns the comment that blocks the four-in-a-row. I have picked the boards so that the AI has to play both players.

### Win-in-one finding testing
For this test, I have selected yet another five boards from different games and of different complexity. All the boards contain a three-in-a-row that the opponent has failed to evade, meaning that the right move will result in an immediate win. I have for each position noted the correct move. The function runs the min-max-function at depth one and asserts that the AI finds the correct move, and also that the score is the appropriate one that should be given when a win is found. The boards have been picked so that both players are represented.

### Find closest win testing
For this test, I used the perfectly playing AI described in the course material to select positions. I have once again picked four different ones. For each one, there is at first a certain win in a certain number of moves, and only one move that is correct. Using the perfectly playing AI I have picked opponent moves (the opponent plays moves automatically), that once again result in a position where there is only one correct move (if there were several, the branching would make the testing incredibly complicated). Now the AI is checked on this position that it finds the right move, the process repeating until the win occurs. If the AI at any point picks the wrong move, the entire test fails. Furthermore, it checks that the AI has detected the win in the right number of moves by asserting that the score that the AI assigns to the move is the appropriate one for a certain win in x number of moves. At any point of the same test, the AI uses the same depth as in the beginning, which is just enough to find the certain win. Both players have different positions that lead to a win, and wins at different depths are represented to make the testing more robust.

### Legal move playing testing
For this test I have picked moves where some of the columns are full and are thus illegal to play. For each of these boards, I have picked out the illegal columns. The function tests each board by looping through all of the columns and checking that the AI does not accept placement in an illegal column and that it does in legal ones.



The tests might be improved by selected even more boards, but the process of picking them has been very tideous, having to calculate the values and input them manually. One might want to implement a test that mirrors the find closest win test, in that it makes sure that the AI manages to stall wins until it is inevitable. Furthermore, the iterative deepening and the precalculated best moves could be tested, but have not thus far as I have seen this as to complicated a task.
