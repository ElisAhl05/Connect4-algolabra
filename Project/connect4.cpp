#include <iostream>
#include "GameController.hpp"

int main() {
	std::cout << "Welcome to Connect 4!" << std::endl;

	auto controller = Connect4::GameController();

	while (true) {
		std::cout << controller.repr() << std::endl;
		std::cout << "Player " << (controller.bTurn ? 1 : 2) << "'s turn. Enter column (1-7): ";
		int col;
		std::cin >> col; col--; // Adjust for 0-based index
		if (!controller.placePiece(col)) {
			std::cout << "Invalid move. Try again." << std::endl;
			continue;
		}
		std::cout << "Eval: " << (controller.getEval() * (!controller.bTurn ? 1 : -1)) << std::endl;
		if (controller.isWin(col)) {
			std::cout << controller.repr() << std::endl;
			std::cout << "Player " << (controller.bTurn ? 2 : 1) << " wins!" << std::endl;
			controller.reset();
		}
	}

	return 0;
}