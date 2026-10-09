#pragma once
#include "../GameController.hpp"
#include "boards.hpp"
#include <iostream>
#include <algorithm>

namespace testing
{
	class Tester {
	private:
		inline bool assert(bool condition) {
			if (!condition) {
				std::cout << "---ASSERTION FAILED!---" << std::endl;
			}
			else {
				std::cout << "Assertion passed!" << std::endl;
			}
			return condition;
		}

		bool testHeuristic() // tests whether the heuristic evaluation function is working correctly
		{
			bool passed_tests = true;
			Connect4::GameController controller;

			std::cout << "Initiating heuristic testing" << std::endl;

			for (const auto& testPair : boards::heuristicTestBoards) {
				auto board = boards::convertToBoard(testPair.moves);
				int heuristic_1 = controller.evalColor(1, board);
				int heuristic_2 = controller.evalColor(2, board);
				passed_tests &= assert(heuristic_1 == testPair.expected_heuristic_1);
				passed_tests &= assert(heuristic_2 == testPair.expected_heuristic_2);
			}
			return passed_tests;
		}

		bool testWinCheck() // tests whether the win detection function is working correctly
		{
			bool passed_tests = true;
			Connect4::GameController controller;

			std::cout << "Initiating win detection testing" << std::endl;

			for (const auto& testPair : boards::winCheckBoards) {
				auto board = boards::convertToBoard(testPair.moves);
				auto lastMove = testPair.moves.back();
				controller.setBoard(board);
				passed_tests &= assert(testPair.isWin == controller.isWin(lastMove));
			}

			return passed_tests;
		}

		bool testAvoidLoss() // tests if AI can avoid losing in one move
		{
			bool passed_tests = true;
			Connect4::GameController controller;

			std::cout << "Initiating loss avoidance testing" << std::endl;

			for (const auto& testPair : boards::avoidLossTestBoards) {
				auto board = boards::convertToBoard(testPair.moves);
				controller.setBoard(board);
				int AI_move = controller.getAIMove(2).bestCol; // 2 layers needed to observe the opponent's moves
				std::cout << "AI did move " << AI_move << ", correct move was " << testPair.best_move << std::endl;
				passed_tests &= assert(testPair.best_move == AI_move);
			}

			return passed_tests;
		}

		bool testFindWin() // tests if AI can find a win in one move
		{
			bool passed_tests = true;
			Connect4::GameController controller;

			std::cout << "Initiating win-in-one finding testing" << std::endl;

			for (const auto& testPair : boards::findWinTestBoards) {
				auto board = boards::convertToBoard(testPair.moves);
				controller.setBoard(board);
				AI_move = controller.getAIMove(1); // The opponent's next move is unneccessary, since there is a win-in-one
				std::cout << "AI did move " << AI_move.bestCol << ", correct move was " << testPair.best_move << std::endl;
				passed_tests &= assert(testPair.best_move == AI_move.bestCol);
				passed_tests &= assert(AI_move.score == Connect4::GameController::fourInARowScore);
			}

			return passed_tests;
		}

		bool testFindClosestWin() // checks whether AI can find wins at the depth it is searching at and lower
		{
			bool passed_tests = true;
			Connect4::GameController controller;

			std::cout << "Initiating closest win finding testing" << std::endl;
			for (const auto& testPair : boards::findFartherWinBoards) {
				int depth = testPair.winning_moves.size();
				auto board = boards::convertToBoard(testPair.moves);
				controller.setBoard(board);
				for (int i = 0; i < depth; i++) {
					std::cout << board.repr() << std::endl;
					auto AI_move = controller.getAIMove(depth);
					std::cout << "AI did move " << AI_move.bestCol << ", correct move was " << testPair.winning_moves[i] << std::endl;
					passed_tests &= assert(testPair.winning_moves[i] == AI_move.bestCol);
					std::cout << "AI score: " << AI_move.score << ", expected score: " << Connect4::GameController::fourInARowScore * (i + 1) << std::endl;
					passed_tests &= assert(AI_move.score == Connect4::GameController::fourInARowScore * (i + 1));
						// assert that the AI has actually detected a win in the right number of moves
					controller.placePiece(testPair.winning_moves[i]);
					i++;
					if (i < depth)
						controller.placePiece(testPair.winning_moves[i]);
				}
			}

			return passed_tests;
		}

		bool testPlaysLegalMoves() // tests whether AI is able to play illegal moves
		{
			bool passed_tests = true;
			Connect4::GameController controller;

			std::cout << "Initiating legal move playing testing" << std::endl;
			for (const auto& testPair : boards::findLegalMovesBoards) {
				std::cout << "{ ";
				for (auto i : testPair.moves) std::cout << i << ", ";
				std::cout << "}\n";
				auto board = boards::convertToBoard(testPair.moves);
				controller.setBoard(board);
				for (int i = 1; i < 7; i++) {
					if (std::find(testPair.illegal_moves.begin(), testPair.illegal_moves.end(), i) != testPair.illegal_moves.end()) {
						assert(controller.placePiece(i) == false); // assert that illegal moves are not allowed
					}
					else {
						assert(controller.placePiece(i) == true); // assert that legal moves are allowed
					}
				}
			}


			return passed_tests;
		}
	public:
		Tester() = default;

		bool testAll()
		{
			bool passed_all_tests = true;

			passed_all_tests &= testHeuristic();
			passed_all_tests &= testWinCheck();
			passed_all_tests &= testAvoidLoss();
			passed_all_tests &= testFindWin();
			passed_all_tests &= testFindClosestWin();
			passed_all_tests &= testPlaysLegalMoves();

			return passed_all_tests;
		}
	};
}