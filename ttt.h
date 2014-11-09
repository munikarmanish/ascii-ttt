#include <stdio.h>		// for printf(), scanf(), getchar()
#include <stdlib.h>		// for srand() and rand()
#include <string.h>		// for string handling functions
#include <ctype.h>
#include <windows.h>	// for gotoxy()
#include <conio.h>		// for getch()

#define VCH 179 // these are boxing characters to print the board
#define HCH 196
#define CCH 197

#define ENTER	13
#define ESC		27
#define	UP		72
#define DOWN	80
#define LEFT	75
#define RIGHT	77

typedef struct record_struct {
	char name[31];
	int score;
	int diff;
} RECORD;

// printing functions

void print_board(int x, int y, int d[9]); // displays board at (x, y)
void print_footer(char* str); // displays footer
void print_heading(void); // displays header
void status(char player[3][31], int wins[3], int draws); // displays wins, loses, draw
void loading(void);

// menu pages

void main_menu(void); // displays main menu
void play(void); // 'Play' page
void about_program(void); // 'About' page
void how_to_play(void); // 'How to play' page
void rules(void); // 'Rule' page
void highscores(int dif); // 'Highscores' page
void single_player(void); // 'Single player' page
void multi_player(void); // 'Multi  player' page

// utility functions

void gotoxy(int x, int y);
char ch(int i);	// returns 'X' or 'O' depending upon board elements
void swap_record(RECORD *R1, RECORD *R2); // swaps two records (for sorting)
char* strin(char *str, int maxlen, FILE *file); // string input function (standard)
int maximum(int a, int b);
int minimum(int a, int b);
int filled(int board[9]); // checks if the board is full
int empty_board(int board[9]); // checks if the board is empty
int iswon(int d[9]); // returns the winner if there is any
int difficulty(void); // returns the difficuly set in the file (default is zero(easy))
char* difficulty_str(int difficulty); // returns 'Easy' for 0 and 'Hard' for 1
void change_difficulty(); // alternates the difficulty betwn 'Easy' and 'Hard'
void save_record(char name[31], int score, int diff); // saves record of last game in file
char* sCase(char *str, int c); // converts a string into uppercase
int nelem(FILE* file, unsigned int elemsize); // returns the count of records of size 'elemsize' in the given binary file

// game playing pages

void start_singleplayer(char player[3][31], int human, int init_turn);
void start_multiplayer(int turn, char player[3][31]); // start human vs human game
void singleplayerUI(int board[9], int moves, int turn, int human);
void multiplayerUI(int board[9], int turn, int moves, char player[3][31]); // displays the board and turn/wins/draw

// Artificial Intelligence functions

int computer_move(int board[9], int human); // returns the best move (position) for computer
int negamax(int board[9], int player);		// returns the best score of a player
