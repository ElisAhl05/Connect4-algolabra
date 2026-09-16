#include <iostream>
#include "GameController.hpp"
#include <chrono>

int main() {
	std::cout << "Welcome to Connect 4!" << std::endl;
	std::cout << "You are Player 1 (X). The AI is Player 2 (O)." << std::endl;
	std::cout << "AI will make a move within 100 milliseconds." << std::endl;

	auto controller = Connect4::GameController();

	int player_turn = 3; // 1 for player 1, 2 for player 2

	while (true) {
		std::cout << controller.repr() << std::endl;
		std::cout << "Player " << (controller.getTurn() ? 1 : 2) << "'s turn. Enter column (1-7): ";
		int col;
		if (controller.getTurn() == player_turn) {
			std::cin >> col; col--; // Adjust for 0-based index
		}
		else {
			col = controller.getAIMove(std::chrono::milliseconds(100)); // AI depth can be adjusted
			std::cout << "AI chooses column: " << (col + 1) << std::endl;
		}
		if (!controller.placePiece(col)) {
			std::cout << "Invalid move. Try again." << std::endl;
			continue;
		}
		std::cout << "Eval: " << (controller.getEval() * (!controller.getTurn() ? 1 : -1)) << std::endl;
		if (controller.isWin(col)) {
			std::cout << controller.repr() << std::endl;
			std::cout << "Player " << (controller.getTurn() ? 2 : 1) << " wins!" << std::endl;
			controller.reset();
		}
	}

	return 0;
}