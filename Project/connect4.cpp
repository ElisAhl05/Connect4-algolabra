#include <iostream>
#include "GameController.hpp"
#include <chrono>
#include <vector>
#include "testing/Testing.hpp"

int main() {
	std::cout << (testing::Tester().testAll() ? "Passed all tests" : "Testing failed") << std::endl;

	std::cout << "Welcome to Connect 4!" << std::endl;
	std::cout << "You are Player 1 (X). The AI is Player 2 (O)." << std::endl;
	std::cout << "AI will make a move within 2 milliseconds." << std::endl;
	std::vector<int> moves;
	auto controller = Connect4::GameController();

	int player_turn = 1; // 1 for player 1, 2 for player 2

	while (true) {
		std::cout << controller.repr() << std::endl;
		std::cout << "Player " << (controller.getTurn() ? 1 : 2) << "'s turn. Enter column (1-7): ";
		int col;
		if (controller.getTurn() == player_turn) {
			std::cin >> col; col--; // Adjust for 0-based index
		}
		else {
			col = controller.getAIMove(2); // AI depth can be adjusted
			std::cout << "AI chooses column: " << (col + 1) << std::endl;
		}
		if (!controller.placePiece(col)) {
			std::cout << "Invalid move. Try again." << std::endl;
			continue;
		}
		std::cout << "Eval: " << (controller.getEval() * (!controller.getTurn() ? 1 : -1)) << std::endl;
		moves.push_back(col);
		std::cout << "Made moves: { ";
		for (auto i : moves) std::cout << i << ", ";
		std::cout << "}" << std::endl;
		if (controller.isWin(col)) {
			moves = {};
			std::cout << controller.repr() << std::endl;
			std::cout << "Player " << (controller.getTurn() ? 2 : 1) << " wins!" << std::endl;
			controller.reset();
		}
	}

	return 0;
}