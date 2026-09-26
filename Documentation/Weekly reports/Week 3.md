# Week 3 report

This week I have done the following changes
- Fixed heuristic function
- Fixed win checks (one direction was not checked before)
- Separated board into a separate board class for easier controll
- Added min-max-algorithm
- Added hashing of boards
- Added a map that matches board states to best move found
- Added alpha-beta-pruning
- Added functionality that makes the AI iterate deeper until a certain time period has elapsed
- Added testing folder which will hold files used for testing
- Added some board states that testing will rely on

The min-max-algorithm works using recursive function calls, where every iteration makes the depth increment until it reaches zero. This way, when the function is called, the number of iterations that the AI should perform are inputted.

Thus, the project is basically finished. Learning about the alpha-beta-pruning took a bit of time, but the min-max-algorithm I had already known from before. Hashing the board was quite interesting, I decided to convert it into a string where every character holds three slots slots on the board (three possible states for every slot, three slots = 81 possible combinations. I have started a bit on the testing front, though no tests are done yet. I intend on testing the heuristic function, the win checks, the map that stores board states with their best moves. Furthermore I will test that the AI can avoid the opponents threats, that it can find win-in-one, that it can find wins in the amount of iterations that it is meant to perform and that it prioritizes closer wins. That it does not play illegal moves could also be tested.

The way I intend on testing this is selecting some five different boards per test, where I have manually calculated what the result should be, where doom is imminent, where the opponent has just won etc. I will then run the respective function on these boards and assert that these give a correct result. Alpha-beta-pruning and the map could also be tested using a version of the min-max function that does not use these functionalities and comparing the results, as these are time-saving add-ons that should not alter the final results. Is there anything more that should be tested? I got some tips from the previous time I tried doing the project on how to do testing in C++ that I will check in on next.

Next week, I should be able to completely finnish the project. I will implement the needed testing and write the proper documentation, also try to tidy and clean the code and add comments. I think I put around 8-10 hours of work into the project this week.
