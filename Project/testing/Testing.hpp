#pragma once
#include "../GameController.hpp"
#include "boards.hpp"
#define CONNECT4_DEBUG true

namespace testing
{
	bool assert(bool condition) {
		if (!condition) {
			std::cerr << "---ASSERTION FAILED!---" << std::endl;
		}
		else {
			std::cout << "Assertion passed!" << std::endl;
		}
			
		return condition;
	}

	void testHeuristic()
	{
		Connect4::GameController controller;
		for (const auto& testPair : boards::heuristicTestBoards) {
			auto board = boards::convertToBoard(testPair.moves);
			int heuristic_1 = controller.evalColor(1, board);
			int heuristic_2 = controller.evalColor(2, board);
			assert(heuristic_1 == testPair.expected_heuristic_1);
			assert(heuristic_2 == testPair.expected_heuristic_2);
		}
	}

	void testWinCheck()
	{

	}

	void testHash()
	{

	}

	void testAvoidLoss()
	{
	
	}

	void testFindWin()
	{
	
	}

	void testFindClosestWin()
	{

	}
}