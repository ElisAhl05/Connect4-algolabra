#pragma once
#include <iostream>
#include <string>
#include <map>
#include <array>
#include <chrono>
#define CONNECT4_DEBUG false

namespace Connect4 {
	static const int rows = 6;
	static const int cols = 7;

	class Board {
	public:
		bool bTurn = 1; // 1 for player 1, 0 for player 2
		int colHeights[cols] = { 0 }; // Track the height of each column
		int board[cols][rows] = { 0 }; // 0 for empty, 1 for player 1, 2 for player 2

		inline bool isValidColumn(int column) {
			return (column >= 0) && (column < cols);
		}

		inline bool isNotFullColumn(int column) {
			return colHeights[column] < rows;
		}

		inline bool isValidPos(int column, int row) {
			return (column >= 0) && (column < cols) && (row >= 0) && (row < colHeights[column]);
		}

		inline int getHeight(int column) {
			return colHeights[column];
		}

		template <bool doCheck = false>
		int getPiece(int column, int row) {
			if constexpr (doCheck) {
				if (column >= 0 && column < cols && row >= 0 && row < colHeights[column]) {
					return board[column][row];
				}
				return -1;
			}
			return board[column][row];
		}

		template <bool doCheck = false>
		bool addPiece(int column) { // returns false if the column is full or invalid, true if the piece was added successfully
			if constexpr (doCheck) {
				if (column >= 0 && column < cols && colHeights[column] < rows) {
					board[column][colHeights[column]] = bTurn ? 1 : 2;
					bTurn = !bTurn; // Switch 
					colHeights[column]++;
					return true;
				}
				return false; // Invalid
			}
			else {
				board[column][colHeights[column]] = bTurn ? 1 : 2;
				bTurn = !bTurn;
				colHeights[column]++;
				return true;
			}
		}

		Board& operator=(const Board& other) {
			if (this != &other) {
				for (int c = 0; c < cols; c++) {
					colHeights[c] = other.colHeights[c];
					for (int r = 0; r < rows; r++) {
						board[c][r] = other.board[c][r];
					}
				}
				bTurn = other.bTurn;
			}
			return *this;
		}

		bool operator==(const Board& other) const {
			for (int c = 0; c < cols; c++) {
				if (colHeights[c] != other.colHeights[c]) return false;
				for (int r = 0; r < rows; r++) {
					if (board[c][r] != other.board[c][r]) return false;
				}
			}
			return bTurn == other.bTurn;
		}

		void undoMove(int column) {
			colHeights[column]--;
			board[column][colHeights[column]] = 0; // Clear the piece
			bTurn = !bTurn; // Switch back the turn
		}

		std::string const hash() { // returns a string representation of the board state for hashing purposes
			char result[15] = { 0 };
			for (int c = 0; c < cols; c++) {
				result[c * 2] = '@' + board[c][0] + board[c][1] * 3 + board[c][2] * 9;
				result[c * 2 + 1] = '@' + board[c][3] + board[c][4] * 3 + board[c][5] * 9;
			}
			return std::string(result);
		}

		std::string const repr() {
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
					result[getPos(r, c)] = symbols[getPiece(c, r)];
				}
				result[getPos(r, -1)] = '|';
				result[getPos(r, cols)] = '|';
				result[getPos(r, cols + 1)] = '\n';
			}
			result[disHeight * disWidth - 1] = '\0'; // Terminate string
			return std::string(result);
		}
	};

	class GameController {
	public:
		Board board;
		int nTurn = 0;

	private:
		std::map<std::string, int> bestMoves;

		void resetBoard() {
			board = Board();
			nTurn = 0;
		}

		bool isWin(int col, Board& checked_board) {
			int inARow = 1;
			int origX = col;
			int origY = checked_board.getHeight(col) - 1;
			int color = checked_board.getPiece(origX, origY);

			// check vertical
			for (int y = origY - 1; y >= 0 && checked_board.getPiece<true>(origX, y) == color; y--) {
				inARow++;
			}
			if (inARow >= 4) return true;

			// check horizontal
			inARow = 1;
			for (int x = origX - 1; x >= 0 && checked_board.getPiece<true>(x, origY) == color; x--) {
				inARow++;
			}
			for (int x = origX + 1; x < cols && checked_board.getPiece<true>(x, origY) == color; x++) {
				inARow++;
			}
			if (inARow >= 4) return true;

			// check diagonal (top-left to bottom-right)
			inARow = 1;
			for (int x = origX - 1, y = origY + 1; x >= 0 && y >= 0 && checked_board.getPiece<true>(x, y) == color; x--, y++) {
				inARow++;
			}
			for (int x = origX + 1, y = origY - 1; x < cols && y < rows && checked_board.getPiece<true>(x, y) == color; x++, y--) {
				inARow++;
			}
			if (inARow >= 4) return true;

			// check other diagonal (top-right to bottom-left)
			inARow = 1;
			for (int x = origX + 1, y = origY + 1; x >= 0 && y < rows && checked_board.getPiece<true>(x, y) == color; x++, y++) {
				inARow++;
			}
			for (int x = origX - 1, y = origY - 1; x < cols && y >= 0 && checked_board.getPiece<true>(x, y) == color; x--, y--) {
				inARow++;
			}
			if (inARow >= 4) return true;

			return false;
		}

		int evalColor(int color, Board& evaled_board) {
			static const int singleScore = 0; // I count them as useless
			static const int doubleScore = 10;
			static const int tripleScore = 100;
			static const int quadScore = 10000; // shouldn't actually occur.

			int streaksFound[4] = { 0, 0, 0, 0 }; // 0: single, 1: double, 2: triple, 3: quad
			int streak = 0;

			// check columns
			for (int x = 0; x < cols; x++) {
				for (int y = 0; y < rows; y++) {
					if (evaled_board.getPiece(x, y) == color) {
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
					if (evaled_board.getPiece(x, y) == color) {
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
			// check diagonals right-down to left-up
			for (int x = 1; x < cols; x++) {
				int i = 0;
				streak = 0;
				while (evaled_board.isValidPos(x - i, i)) {
					if (evaled_board.getPiece(x - i, i) == color)
						streak++;
					else {
						if (streak) streaksFound[streak - 1]++;
						streak = 0;
					}
					i++;
				}
				if (streak) streaksFound[streak - 1]++;
			}
			int x = cols - 1;
			for (int y = 1; y < rows - 1; y++) { // note the rows - 1 and the startX = 1: The bottom left and top right cornes cannot contain anything valuable
				int i = 0;
				streak = 0;
				while (evaled_board.isValidPos(x - i, y + i)) {
					if (evaled_board.getPiece(x - i, y + i) == color)
						streak++;
					else {
						if (streak) streaksFound[streak - 1]++;
						streak = 0;
					}
					i++;
				}
				if (streak) streaksFound[streak - 1]++;
			}
			// check diagonals left-down to right-up
			for (int x = 0; x < cols - 1; x++) { // when x = columns - 1, the diagonal is one block large and thus unneccessary.
				int i = 0;
				streak = 0;
				while (evaled_board.isValidPos(x + i, i)) {
					if (evaled_board.getPiece(x + i, i) == color)
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
				streak = 0;
				while (evaled_board.isValidPos(i, y + i)) {
					if (evaled_board.getPiece(i, y + i) == color)
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
			return evalColor(1, board) - evalColor(2, board); // Player 1 score - Player 2 score
		}

		inline int eval(Board& evaled_board, bool player = 1) {
			return evalColor(2 - player, evaled_board) - evalColor(1 + player, evaled_board);
		}

		struct minMaxResult {
			int score;
			int bestCol; // Perhaps the column isn't neccessary.
		};

		minMaxResult minMax(Board& working_board, int depth, bool player, bool turn, int alpha, int beta) {
			static const int largeVal = 10000000;
			static const int fourInARowScore = 100000;
			static const std::array<int, 7> columnOrdersIfMapped[7] = {
				{ 0, 3, 2, 4, 1, 5, 6 }, // If the board already has a best move stored (namely 0),
				{ 1, 3, 2, 4, 5, 0, 6 }, // the first row will be used for ordering checks. If the best
				{ 2, 3, 4, 1, 5, 0, 6 }, // move is 1, the second row, and so on.
				{ 3, 2, 4, 1, 5, 0, 6 },
				{ 4, 3, 2, 1, 5, 0, 6 },
				{ 5, 3, 2, 4, 1, 0, 6 },
				{ 6, 3, 2, 4, 1, 5, 0 }
			};

			if (depth == 0) {
				return { eval(working_board, player), -1 };;
			}
			auto hash_value = working_board.hash();
			std::array<int, 7> priorityOrder = { 3, 2, 4, 1, 5, 0, 6 }; // default priority, starting in the middle
			if (bestMoves.find(hash_value) != bestMoves.end()) { // this should be tested a bit more, it seems that the matches turn up one iteration too late.
				priorityOrder = columnOrdersIfMapped[bestMoves[hash_value]];
			}
			if (turn == player) {
				int max_score = -largeVal;
				int bestCol = -1;
				for (int col : priorityOrder) {
					if (working_board.addPiece<true>(col)) {
						if (isWin(col, working_board)) {
							working_board.undoMove(col);
							bestMoves[working_board.hash()] = col;
							int score = fourInARowScore * (depth + 1);
							alpha = alpha > score ? alpha : score; // Update alpha
							return { score, col }; // * (depth + 1) makes AI tend to closer wins 
						}

						auto score = minMax(working_board, depth - 1, player, !turn, alpha, beta);
						working_board.undoMove(col);
						if (score.score > max_score) {
							max_score = score.score;
							bestCol = col;
							alpha = alpha > max_score ? alpha : max_score;
							if (max_score >= beta) { // Beta cut-off
								break;
							}
						}
					}
				}
				bestMoves[hash_value] = bestCol; // Store the best move for this board state
				return { max_score, bestCol };
			}
			else {
				int min_score = largeVal;
				int bestCol = -1;
				for (int col : priorityOrder) {
					if (working_board.addPiece<true>(col)) {
						if (isWin(col, working_board)) {
							working_board.undoMove(col);
							bestMoves[working_board.hash()] = col;
							int score = -fourInARowScore * (depth + 1);
							beta = beta < score ? beta : score; // Update beta
							return { score, col }; // * (depth + 1) makes AI tend to closer wins 
						}
						auto score = minMax(working_board, depth - 1, player, !turn, alpha, beta);
						working_board.undoMove(col);
						if (score.score < min_score) {
							min_score = score.score;
							bestCol = col;
							beta = beta < min_score ? beta : min_score;
							if (min_score <= alpha) { // Alpha cut-off
								break;
							}
						}
					}
				}
				bestMoves[hash_value] = bestCol;
				return { min_score, bestCol };
			}

		}



	public:
		GameController() = default;

		void reset() {
			resetBoard();
			nTurn = 0;
		}

		bool getTurn() {
			return nTurn % 2 == 0; // true for player 1, false for player 2
		}

		int getAIMove(int depth) {
			bestMoves.clear(); // Clear the map of best moves
			auto result = minMax(board, depth, board.bTurn, board.bTurn, -100000000, 100000000);
			std::cout << "AI evaluated score: " << result.score << std::endl;
			return result.bestCol;
		}

		int getAIMove(std::chrono::milliseconds timeLimit) {
			minMaxResult bestResult = { -10000000, -1 };
			auto start = std::chrono::high_resolution_clock::now();
			int iterations = 0;
			bestMoves.clear(); // Clear the map of best moves
			while (std::chrono::high_resolution_clock::now() - start < timeLimit && (6 * 7 - nTurn - iterations) > 0) {
				iterations++;
				bestResult = minMax(board, iterations, board.bTurn, board.bTurn, -100000000, 100000000);
			}
			std::cout << "AI evaluated score: " << bestResult.score << std::endl;
			std::cout << "AI did " << iterations << " iterations" << std::endl;
			return bestResult.bestCol;
		}

		bool placePiece(int col) {
			if (board.addPiece<true>(col)) {
				nTurn++;
				return true;
			}
			return false; // Invalid
		}

		int getEval() {
			return eval();
		}

		bool isWin(int col) {
			return isWin(col, board);
		}

		inline std::string repr() { // will overload << in the future, did not get it working right now
			return board.repr();
		}
	};
}