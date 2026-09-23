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
			for (auto move : moves) board.addPiece(move);
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
			{ { 3, 2, 2, 3, 5, 6, 6, 2, 4}, 120 /* 2 double, 1 triple */, 20 /* 2 doubles */ },
			/*/-------\
			  |.......|
			  |.......|
			  |.......|
			  |..O....|
			  |..XO..X|
			  |..OXXXO|
			  \1234567/ */
			{ { 6, 1, 5, 3, 5, 5, 3, 2, 3, 1, 2, 6, 3, 5, 2, 3, 6 }, 200 /* 10 doubles, 1 triple*/, 140 /*4 doubles 1 triple*/},
			/*/-------\
			  |.......|
			  |...O...|
			  |...X.O.|
			  |..XX.OX|
			  |.OXX.XO|
			  |.OOO.XX|
			  \1234567/*/
			{ { 3, 2, 4, 2, 5, 6, 4, 4, 5, 3, 3, 4, 4, 3, 6, 6, 3, 1, 6, 5, 5, 5, 1, 1},
			8 * 10 + 3 * 100, 10 * 10 + 2 * 100 },
			/*/-------\
			  |.......|
		 	  |...XXO.|
			  |...OOXX|
			  |.O.XOOO|
			  |.XOOXXX|
			  |.OOXXXO|
			  \1234567/*/
			{ { 3, 2, 2, 3, 3, 1, 1, 2, 1, 1, 4, 5, 2, 4, 5, 1, 4, 3, 4, 4, 0, 3, 2, 0, 5, 3, 4},
			(4 + 2 + 3 + 3) * 10 + 3 * 100, (3 + 1 + 3 + 1) * 10 + 3 * 100},
			/*/-------\
			  |...OX..|
			  |.OXOO..|
			  |.OXOX..|
			  |.XOXXX.|
			  |OXXOOX.|
			  |XOOXXO.|
			  \1234567/*/
			{ { 3, 6, 1, 2, 4, 2, 6, 4, 2, 4, 5 },
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
	
		struct winCheckTestPair {
			std::vector<int> moves = {};
			bool isWin = false;
		};

		std::vector<winCheckTestPair> winCheckBoards = {
			{ { 3, 2, 0, 2, 2, 3, 1, 1, 0, 4, 1, 4 }, true },
		  /*/-------\
			|.......|
			|.......|
			|.......|
			|.XX....|
			|XOOOO..|
			|XXOXO..|
			\1234567/*/
			{ { 6, 3, 1, 3, 2, 3, 3, 2, 2, 1, 6, 4, 4, 0, 0, 1, 5, 1 }, false },
		  /*/-------\
			|.......|
			|.......|
			|.O.X...|
			|.OXO...|
			|XOOOX.X|
			|OXXOOXX|
			\1234567/*/
			{ { 3, 3, 3, 3, 2, 1, 1, 4, 1, 1, 0, 4, 4, 4, 6, 0, 3,
			4, 4, 3, 6, 6, 6, 6, 1, 5, 5, 5, 5, 5, 1, 5, 6, 0, 0, 2, 2 }, true },
		  /*/-------\
			|.X.OXOX|
			|.X.XOOO|
			|XO.OOXX|
			|OXXXXOO|
			|OXOOOXX|
			|XOXXOOX|
			\1234567/*/
			{ { 2, 3, 3, 5, 4, 5, 4, 5, 5, 4, 3, 3, 6, 4 }, false },
		  /*/-------\
			|.......|
			|.......|
			|...OOX.|
			|...XOO.|
			|...XXO.|
			|..XOXOX|
			\1234567/*/
			{ { 3, 2, 3, 1, 2, 1, 1, 2, 0, 2, 4, 2, 2, 4, 3, 3, 1, 4, 4, 4 }, true }
		  /*/-------\
			|..X....|
			|..O.O..|
			|.XOOX..|
			|.XOXO..|
			|.OXXO..|
			|XOOXX..|
			\1234567/*/
		};

		struct findMoveTestPair {
			std::vector<int> moves;
			int best_move = 0;
		};

		std::vector<findMoveTestPair> findWinTestBoards = {
			{ { 3, 2, 2, 3, 0, 3, 3, 4, 2, 2, 4, 4, 5, 5, 6, 5, 0 }, 5 },
		  /*/-------\
			|.......|
			|.......|
			|..OX...|
			|..XOOO.|
			|X.XOXO.|
			|X.OXOXX|
			\1234567/*/
			{ { 3, 1, 1, 2, 2, 0, 0, 0 }, 3 },
		  /*/-------\
			|.......|
			|.......|
			|.......|
			|O......|
			|XXX....|
			|OOOX...|
			\1234567/*/
			{ { 2, 3, 3, 4, 4, 1, 4, 5, 5 }, 6 },
		  /*/-------\
			|.......|
			|.......|
			|.......|
			|....X..|
			|...XXX.|
			|.OXOOO.|
			\1234567/*/
			{ { 3, 1, 2, 2, 6, 4, 4, 5, 3, 4, 5, 6, 5, 2, 2, 3, 4, 3, 0, 4, 3 }, 1 },
		  /*/-------\
			|.......|
			|...XO..|
			|..XOX..|
			|..OOOX.|
			|..OXXXO|
			|XOXXOOX|
			\1234567/*/
			{ { 3, 2, 6, 4, 3, 5, 2, 4, 6, 4, 1 }, 4 }
		  /*/-------\
			|.......|
			|.......|
			|.......|
			|....O..|
			|..XXO.X|
			|.XOXOOX|
			\1234567/*/
		};

		std::vector<findMoveTestPair> avoidLossTestBoards = {
			{ { 3, 1, 1, 2, 2, 0, 0 }, 3 },
		  /*/-------\
			|.......|
			|.......|
			|.......|
			|.......|
			|XXX....|
			|OOOX...|
			\1234567/*/
			{ { 2, 3, 3, 4, 4, 1, 4, 5}, 6 },
		  /*/-------\
			|.......|
			|.......|
			|.......|
			|....X..|
			|...XX..|
			|.OXOOO.|
			\1234567/*/
			{ { 3, 1, 2, 2, 6, 4, 4, 5, 3, 4, 5 }, 6 },
		  /*/-------\
			|.......|
			|.......|
			|.......|
			|....O..|
			|..OXXX.|
			|.OXXOOX|
			\1234567/*/
			{ { 3, 3, 6, 3, 2, 3, 3, 2, 2, 1, 1, 2, 4, 5, 4, 4 }, 4 },
		  /*/-------\
			|.......|
			|...X...|
			|..OO...|
			|..XOO..|
			|.XOOX..|
			|.OXXXOX|
			\1234567/*/
			{ { 3, 2, 6, 4, 3, 5, 2, 4, 6, 4 }, 4 }
		  /*/-------\
			|.......|
			|.......|
			|.......|
			|....O..|
			|..XXO.X|
			|..OXOOX|
			\1234567/*/
		};

		struct findLegalMovesTestPair {
			std::vector<int> moves;
			std::vector<int> illegal_moves;
		};

		std::vector<findLegalMovesTestPair> findLegalMovesBoards = {
			{ { 3, 3, 2, 3, 3, 2, 2, 1, 1, 0, 6, 4, 4, 4, 4, 4, 2, 2, 3, 3, 2, 4 }, { 2, 3, 4 } },
		  /*/-------\
			|..XOO..|
			|..OXO..|
			|..XXX..|
			|..XOO..|
			|.XOOX..|
			|OOXXO.X|
			\1234567/*/
			{ { 3, 2, 3, 1, 3, 3, 5, 6, 4, 5, 2, 6, 1, 4, 4, 6, 6, 2, 5, 5, 4, 5, 4, 4, 1, 3, 1, 1, 0, 0, 0, 0, 3, 0, 0, 5 }, { 0, 3, 4, 5 } },
		  /*/-------\
			|X..XOO.|
			|OO.OXO.|
			|OX.OXOX|
			|XXOXXXO|
			|OXXXOOO|
			|XOOXXXO|
			\1234567/*/
			{ { 4, 3, 4, 4, 3, 3, 3, 1, 0, 1, 5, 1, 1, 5, 4, 2, 5, 5, 6, 6, 3, 0, 4, 0, 0, 5, 5, 4, 3, 1, 0, 0, 1, 6, 6, 6, 6 }, { 0, 1, 3, 4, 5, 6 } },
		  /*/-------\
			|OX.XOXX|
			|XO.XXOO|
			|XX.XXOX|
			|OO.OOXO|
			|OO.XXOO|
			|XOOOXXX|
			\1234567/*/
			{ { 4, 3, 4, 4, 3, 3, 3, 1, 0, 1, 5, 1, 1, 5, 4, 2, 5, 5, 6, 6, 3, 4, 3, 0, 6, 6, 4, 6, 6, 1, 1, 0, 0, 0, 0 }, { 0, 1, 3, 4, 6 } },
		  /*/-------\
			|XX.XX.X|
			|OO.XO.O|
			|XX.XXOO|
			|OO.OOXX|
			|OO.XXOO|
			|XOOOXXX|
			\1234567/*/
			{ { 5, 4, 5, 5, 4, 4, 2, 5, 3, 5, 5, 3, 1, 0, 3, 4, 4, 3, 1, 3 }, { 5 } },
		  /*/-------\
			|.....X.|
			|...OXO.|
			|...OOO.|
			|...XOO.|
			|.X.OXX.|
			|OXXXOX.|
			\1234567/*/
			{ { 5, 4, 5, 5, 4, 4, 4, 2, 1, 2, 2, 5, 5, 1, 1, 1, 4, 4, 2, 2, 6, 6, 6, 1, 1, 5, 2, 6, 6, 6, 0, 0 }, { 1, 2, 4, 5, 6 } }
		  /*/-------\
			|.XX.OOO|
			|.OO.XXX|
			|.OX.XOO|
			|.XX.OOX|
			|OOO.XXO|
			|XXO.OXX|
			\1234567/*/
		};
	}
}