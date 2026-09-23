#pragma once
#include "../GameController.hpp"
#include "boards.hpp"
#include <iostream>

namespace testing
{
	class Tester {
	private:
		bool assert(bool condition) {
			if (!condition) {
				std::cout << "---ASSERTION FAILED!---" << std::endl;
			}
			else {
				std::cout << "Assertion passed!" << std::endl;
			}
			return condition;
		}

		bool testHeuristic()
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

		bool testWinCheck()
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

		bool testHash()
		{
			bool passed_tests = true;

			std::cout << "Initiating hash testing" << std::endl;

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
				int AI_move = controller.getAIMove(2); // Only does one layer
				std::cout << "AI did move " << AI_move << ", correct move was " << testPair.best_move << std::endl;
				passed_tests &= assert(testPair.best_move == AI_move);
			}

			return passed_tests;
		}

		bool testFindWin()
		{
			bool passed_tests = true;

			std::cout << "Initiating heuristic testing" << std::endl;

			return passed_tests;
		}

		bool testFindClosestWin()
		{
			bool passed_tests = true;

			std::cout << "Initiating closest win finding testing" << std::endl;

			return passed_tests;
		}

		bool testPlaysLegalMoves()
		{
			bool passed_tests = true;

			std::cout << "Initiating legal move playing testing" << std::endl;

			return passed_tests;
		}
	public:
		Tester() = default;
		bool testAll(bool print = true)
		{
			bool passed_all_tests = true;

			passed_all_tests &= testHeuristic();
			passed_all_tests &= testWinCheck();
			passed_all_tests &= testHash();
			passed_all_tests &= testAvoidLoss();
			passed_all_tests &= testFindWin();
			passed_all_tests &= testFindClosestWin();
			passed_all_tests &= testPlaysLegalMoves();

			return passed_all_tests;
		}
	};
}