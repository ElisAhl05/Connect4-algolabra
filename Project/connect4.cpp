#include <iostream>
#include "GameController.hpp"

int main() {
	std::cout << "Welcome to Connect 4!" << std::endl;

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
			col = controller.getAIMove(5); // AI depth can be adjusted
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