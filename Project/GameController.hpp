#pragma once
#include <string>

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