#include "ttt.h"

int computer_move(int board[9], int human) {
	int computer = human * -1;
	int diff = difficulty();

	// start at random
	if (empty_board(board)) return (rand() % 9);

	// check if there is winning move
	int i;
	for (i=0; i<9; i++) { // for all the positions
		if (board[i]==0) { // if the position is empty
			board[i] = computer; // try the move
			if (iswon(board) == computer) {
				board[i] = 0;
				return i;
			}
			board[i] = 0;
		}
	}

	// for medium difficulty, check if there is blocking move
	if (diff >= 1) {
		for (i=0; i<9; i++) {
			if (board[i] == 0) {
				board[i] = human;
				if (iswon(board) == human) {
					board[i] = 0;
					return i;
				}
				board[i] = 0;
			}
		}
	}

	// for hard difficulty, make the computer unbeatable
	int bestMove, best = -2;
	if (diff >= 2) {
		for (i=0; i<9; i++) {
			if (board[i]==0) {
				board[i] = computer;
				int score = -negamax(board, human);
				board[i] = 0;

				if (score > best) {
					best = score;
					bestMove = i;
				}
			}
		}
		return bestMove;
	}

	// or place anywhere in the blank spot
	int blank[9] = {0,0,0,0,0,0,0,0,0};
	int blank_count = 0;
	for (i=0; i<9; i++)
		if (board[i] == 0)
			blank[blank_count++] = i;
	return blank[rand() % blank_count];
}

int negamax(int board[9], int player) {
	// check if terminal node
	if (iswon(board)) return iswon(board)*player;
	else if (filled(board) && !iswon(board)) return 0;

	int best = -2;
	int i;
	for (i=0; i<9; i++) {
		if (board[i] == 0) {
			board[i] = player;
			int score = -negamax(board, player*-1);
			board[i] = 0;

			best = maximum(best, score);
		}
	}

	return best;
}
