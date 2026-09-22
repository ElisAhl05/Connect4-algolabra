#pragma once
#include "../GameController.hpp"
#include <vector>
#include <iostream>

namespace testing
{
	namespace boards
	{
		Connect4::Board convertToBoard(std::vector<int> moves)
		{
			static const bool debugConversion = true;
			Connect4::Board board;
			for (auto move : moves) board.addPiece(move - 1);
			if constexpr (debugConversion) std::cout << board.repr() << std::endl;
			return board;
		}

		struct heuristicTestPair {
			std::vector<int> moves = {};
			int expected_heuristic_1 = 0; // X on the board
			int expected_heuristic_2 = 0; // O on the board
		};

		// doubles get 10, triples 100

		std::vector<heuristicTestPair> heuristicTestBoards = {
			{ { 4, 3, 3, 4, 6, 7, 7, 3, 5}, 120 /* 2 double, 1 triple */, 20 /* 2 doubles */ },
			/*/-------\
			  |.......|
			  |.......|
			  |.......|
			  |..O....|
			  |..XO..X|
			  |..OXXXO|
			  \1234567/ */
			{ { 7, 2, 6, 4, 6, 6, 4, 3, 4, 2, 3, 7, 4, 6, 3, 4, 7 }, 170 /* 7 doubles, 1 triple*/, 140 /*4 doubles 1 triple*/},
			/*/-------\
			  |.......|
			  |...O...|
			  |...X.O.|
			  |..XX.OX|
			  |.OXX.XO|
			  |.OOO.XX|
			  \1234567/*/
			{ { 4, 3, 5, 3, 6, 7, 5, 5, 6, 4, 4, 5, 5, 4, 7, 7, 4, 2, 7, 6, 6, 6, 2, 2},
			8 * 10 + 3 * 100, 10 * 10 + 2 * 100 },
			/*/-------\
			  |.......|
		 	  |...XXO.|
			  |...OOXX|
			  |.O.XOOO|
			  |.XOOXXX|
			  |.OOXXXO|
			  \1234567/*/
			{ { 4, 3, 3, 4, 4, 2, 2, 3, 2, 2, 5, 6, 3, 5, 6, 2, 5, 4, 5, 5, 1, 4, 3, 1, 6, 4, 5},
			(4 + 2 + 3 + 3) * 10 + 3 * 100, (3 + 1 + 3 + 1) * 10 + 3 * 100},
			/*/-------\
			  |...OX..|
			  |.OXOO..|
			  |.OXOX..|
			  |.XOXXX.|
			  |OXXOOX.|
			  |XOOXXO.|
			  \1234567/*/
			{ { 4, 7, 2, 3, 5, 3, 7, 5, 3, 5, 6 },
			(1 * 10 + 1 * 100 /*1 double,1 triple*/), 2 * 10 /*2 doubles*/}

			/*/-------\
			  |.......|
			  |.......|
			  |.......|
			  |..X.O..|
			  |..O.O.X|
			  |.XOXXXO|
			  \1234567/*/
		};
	}
}