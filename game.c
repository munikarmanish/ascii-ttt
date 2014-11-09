#include "ttt.h"

void start_multiplayer(int init_turn, char player[3][31]) {
	int turn_start = init_turn;
	int wins[3]={0,0,0}, draws=0; // initializing the number of wins and draws

	// while user wants to play new game (after completing one game)
	int newgame=1;
	while (newgame==1) {
		int board[9] = {0,0,0,0,0,0,0,0,0}; // initialize board before every game

		int turn = turn_start;
		int c, pos=0, moves=0;

		multiplayerUI(board, turn, moves, player); // show the current board, and turn/win/draw

		int x=22, y=6; // this is necessary for arrow controls
		gotoxy(x, y);

		int ask=1;
		while (ask==1 && (c=getch())) {
			if (c==ESC) 				{ status(player, wins, draws); } // if [Esc], show the current game status
			else if (c==UP && y>6) 		{ gotoxy(x, y-=4); pos-=3; }
			else if (c==DOWN && y<14) 	{ gotoxy(x, y+=4); pos+=3; }
			else if (c==LEFT && x>22) 	{ gotoxy(x-=6, y); pos--; }
			else if (c==RIGHT && x<34) 	{ gotoxy(x+=6, y); pos++; }

			else if (c==ENTER && board[pos]==0 && moves<9) {
				board[pos]=turn; 	// if user presses [Enter] in blank spot, play that move
				turn *= -1;			// and then change the turn
				moves++;			// and increase the moves count
			}

			multiplayerUI(board, turn, moves, player);	// show the board and turn/win/draw
			gotoxy(x, y);

			// after every move, check if its game-over
			int winner;
			if (winner=iswon(board)) {
				wins[winner+1]++;
				newgame=1; ask=0;
				turn_start *= -1;
				getch();
			}

			if (moves==9 && iswon(board)==0) {
				draws++;
				newgame=1; ask=0;
				turn_start *= -1;
				getch();
			}
		}
	}
}

void start_singleplayer(char player[3][31], int human, int init_turn) {
	int computer = human *-1;
	int turn_start = init_turn;
	int wins[3]={0,0,0}, draws=0, diff=difficulty();

	int newgame=1;
	while (newgame==1) {
		int board[9]={0,0,0,0,0,0,0,0,0};
		int c, pos=0, moves=0;
		int turn = turn_start;

		singleplayerUI(board, moves, turn, human);

		int x=22, y=6;
		gotoxy(x,y);

		int ask=1;
		while (ask==1) {
			if (turn==human && moves<9 && iswon(board)==0) {
				c = getch();
				if (c==ESC)	{
					int score = wins[human+1] - wins[computer+1];
					save_record(player[human+1], score, difficulty());
					status(player, wins, draws);
				}
				else if (c==UP && y>6)    { y -= 4; pos -= 3; }
				else if (c==DOWN && y<14) { y+=4; pos+=3; }
				else if (c==LEFT && x>22) { x-=6; pos-=1; }
				else if (c==RIGHT && x<34) { x+=6; pos+=1; }
				else if (c==ENTER && board[pos]==0) {
					board[pos] = human;
					turn *= -1;
					moves++;
				}
			}
			else if (turn==computer && moves<9 && iswon(board)==0) {

				int j;
				for (j=0; j<300000000; j++); // delay for a second

				int bestMove = computer_move(board, human);
				board[bestMove]=computer;
				turn *= -1;
				moves++;
			}

			singleplayerUI(board, moves, turn, human);
			gotoxy(x, y);

			int winner;
			if (winner=iswon(board)) {
				wins[winner+1]++;
				newgame=1; ask=0;
				turn_start *= -1;
				getch();
			}

			if (moves==9 && iswon(board)==0) {
				draws++;
				newgame=1; ask=0;
				turn_start *= -1;
				getch();
			}
		}
	}
}

void multiplayerUI(int board[9], int turn, int moves, char player[3][31]) {
	system("cls");
	print_heading();
	print_footer("Press [Esc] to end the game");

	print_board(20,5, board);

	gotoxy(20, 18);

	int winner;
	if (winner=iswon(board))
		printf("%s (%c) WINS! Press any key...", player[winner+1], ch(winner));

	else if (moves==9)
		printf("A DRAW! Press any key...");

	else
		printf("%s's turn (%c)", player[turn+1], ch(turn));
}

void singleplayerUI(int board[9], int moves, int turn, int human) {
	system("cls");
	print_heading();
	print_footer("Press [Esc] to end the game");

	print_board(20,5,board);

	gotoxy(20,18);

	int winner;
	if (winner = iswon(board)) {
		if (winner==human) printf("CONGRATULATION! YOU WIN!");
		else printf("BOOO! YOU LOSE! Better luck next time!");
	}
	else if (moves==9)
		printf("A DRAW! Press any key...");
	else {
		if (turn==human) printf("Your turn");
		else printf("COMPUTER's turn");
	}

}
