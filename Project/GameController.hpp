#pragma once
#include <iostream>
#include <string>
#define CONNECT4_DEBUG true

namespace Connect4 {
	class GameController {
	public:
		static const int rows = 6;
		static const int cols = 7;

		bool bTurn = true; // true for player 1, false for player 2
		int nTurn = 0;

		int colHeights[cols] = { 0 }; // Track the height of each column
		int board[cols][rows] = { 0 }; // 0 for empty, 1 for player 1, 2 for player 2

	private:
		void resetBoard() {
			bTurn = true;
			for (int c = 0; c < cols; c++) {
				colHeights[c] = 0;
				for (int r = 0; r < rows; r++) board[c][r] = 0;
			}
			nTurn = 0;
		}

		inline bool validPos(int column, int row) {
			return (column >= 0) && (column < cols) && (row >= 0) && (row < rows);
		}

		template <bool doCheck = false>
		inline int getPiece(int column, int row) {
			if constexpr (doCheck) {
				if (validPos(column, row)) return board[column][row];
				return -1; // Invalid
			}
			return board[column][row];
		}

		unsigned int evalColor(int color) {
			static const int singleScore = 0;
			static const int doubleScore = 10;
			static const int tripleScore = 100;
			static const int quadScore   = 10000;

			int streaksFound[4] = { 0, 0, 0, 0 }; // 0: single, 1: double, 2: triple, 3: quad
			int streak = 0;

			// check columns
			for (int x = 0; x < cols; x++) {
				for (int y = 0; y < rows; y++) {
					if (getPiece(x, y) == color) {
						streak++;
					}
					else {
						if (streak > 0 && streak <= 4) streaksFound[streak - 1]++;
						streak = 0;
					}
				}
				if (streak > 0 && streak <= 4) {
					streaksFound[streak - 1]++;
					streak = 0;
				}
			}

			// check rows
			for (int y = 0; y < rows; y++) {
				for (int x = 0; x < cols; x++) {
					if (getPiece(x, y) == color) {
						streak++;
					}
					else {
						if (streak > 0 && streak <= 4) streaksFound[streak - 1]++;
						streak = 0;
					}
				}
				if (streak > 0 && streak <= 4) {
					streaksFound[streak - 1]++;
					streak = 0;
				}
			}
			// check diagonals left-down to right-up
			for (int x = 0; x < cols - 1; x++) { // when x = columns - 1, the diagonal is one block large and thus unneccessary.
				int i = 0;
				while (validPos(x + i, i)) {
					if (getPiece(x + i, i) == color)
						streak++;
					else {
						if (streak > 0 && streak <= 4) streaksFound[streak - 1]++;
						streak = 0;
					}
					i++;
				}
				if (streak > 0 && streak <= 4) {
					streaksFound[streak - 1]++;
					streak = 0;
				}
			}
			for (int y = 1; y < rows - 1; y++) { // when y = rows - 1, the diagonal is one block large
				int i = 0;
				while (validPos(i, y + i)) {
					if (getPiece(i, y + i) == color)
						streak++;
					else {
						if (streak > 0 && streak <= 4) streaksFound[streak - 1]++;
						streak = 0;
					}
					i++;
				}
				if (streak > 0 && streak <= 4) {
					streaksFound[streak - 1]++;
					streak = 0;
				}
			}

			if constexpr (CONNECT4_DEBUG) {
				std::cout << "Streaks found for color " << color << ": ";
				for (int i = 0; i < 4; i++) {
					std::cout << streaksFound[i] << " ";
				}
				std::cout << std::endl;
			}

			return streaksFound[0] * singleScore
				 + streaksFound[1] * doubleScore
				 + streaksFound[2] * tripleScore
				 + streaksFound[3] * quadScore;
		}

		inline int eval() {
			return evalColor(1) - evalColor(2); // Player 1 score - Player 2 score
		}

	public:
		GameController() = default;

		void reset() {
			resetBoard();
		}

		bool placePiece(int col) {
			if (col >= 0 && col < cols && colHeights[col] < rows) {
				board[col][colHeights[col]] = bTurn ? 1 : 2;
				colHeights[col]++;

				bTurn = !bTurn;
				return true;
			}
			return false; // Invalid
		}

		bool isWin(int col) {
			int inARow = 1;
			int origX = col;
			int origY = colHeights[col] - 1;
			int color = getPiece(origX, origY);

			// check vertical
			for (int y = origY - 1; y >= 0 && getPiece(origX, y) == color; y--) {
				inARow++;
			}
			if (inARow >= 4) return true;

			// check horizontal
			for (int x = origX - 1; x >= 0 && getPiece(x, origY) == color; x--) {
				inARow++;
			}
			for (int x = origX + 1; x < cols && getPiece(x, origY) == color; x++) {
				inARow++;
			}
			if (inARow >= 4) return true;

			// check diagonal (top-left to bottom-right)
			inARow = 1;
			for (int x = origX - 1, y = origY - 1; x >= 0 && y >= 0 && getPiece(x, y) == color; x--, y--) {
				inARow++;
			}
			for (int x = origX + 1, y = origY + 1; x < cols && y < rows && getPiece(x, y) == color; x++, y++) {
				inARow++;
			}
			if (inARow >= 4) return true;

			// check other diagonal (top-right to bottom-left)
			inARow = 1;
			for (int x = origX - 1, y = origY + 1; x >= 0 && y < rows && getPiece(x, y) == color; x--, y--) {
				inARow++;
			}
			for (int x = origX + 1, y = origY - 1; x < cols && y >= 0 && getPiece(x, y) == color; x++, y++) {
				inARow++;
			}
			if (inARow >= 4) return true;

			return false;
		}

		int getEval() {
			return eval();
		}

		std::string repr() { // will overload << in the future, did not get it working right now
			static const char symbols[3] = { '.', 'X', 'O' };
			static const char numChart[7] = { '1', '2', '3', '4', '5', '6', '7' };

			static const int disWidth = cols + 3;
			static const int disHeight = rows + 2;

			auto getPos = [](int row, int col) {
				return (rows - row) * disWidth + col + 1;
				};

			char result[disHeight * disWidth];

			for (int c = 0; c < cols; ++c) {
				result[getPos(-1, c)] = numChart[c];
				result[getPos(rows, c)] = '-';
			}

			result[0] = '/';
			result[disWidth - 2] = '\\';
			result[disWidth - 1] = '\n';
			result[disWidth * (disHeight - 1)] = '\\';
			result[disWidth * disHeight - 2] = '/';

			for (int r = rows - 1; r >= 0; --r) {
				for (int c = 0; c < cols; ++c) {
					result[getPos(r, c)] = symbols[board[c][r]];
				}
				result[getPos(r, -1)] = '|';
				result[getPos(r, cols)] = '|';
				result[getPos(r, cols + 1)] = '\n';
			}
			result[disHeight * disWidth - 1] = '\0'; // Terminate string
			return std::string(result);
		}
	};
}