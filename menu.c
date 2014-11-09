#include "ttt.h"

void main_menu(void) {
	system("cls");                             // print the header & footer
	print_heading();
	print_footer("Press [Esc] to quit");

	int diff = difficulty();

	gotoxy(0, 5);
	printf("%s",
			"    MAIN MENU | Choose an option                           \n"
			"                                                           \n"
			"     [1]  Play the game                                    \n"
			"     [2]  Rules of the game                                \n");
	printf( "     [3]  Difficulty: %s \n", difficulty_str(diff));
	printf("%s",
			"     [4]  How to play                                      \n"
			"     [5]  Highscores                                       \n"
			"     [6]  About                                            \n");

	char choice = getch();
	switch (choice) {
		case '1': play(); break;
		case '2': rules(); break;
		case '4': how_to_play(); break;
		case '5': highscores(diff); break;
		case '6': about_program(); break;
		case '3': change_difficulty(); main_menu(); break;
		case ESC: exit(0);
		default:  main_menu(); break;
	}
}

void about_program(void) {
	system("cls");
	print_heading();
	print_footer("Press [Esc] to goto Main Menu");

	gotoxy(0, 5);
	printf("%s",
		"    ABOUT THIS PROGRAM:                                       \n"
		"                                                              \n"
		"    TIC-TAC-TOE is a small console-based mind-game developed \n"
		"    by Brihat Ratna Bajracharya (070-BCT-513) and Manish    \n"
		"    Munikar (070-BCT-520) as a mini-project in the first    \n"
		"    semester at Pulchowk Campus, IOE.                       \n"
		"                                                              \n"
		"    Find Brihat @ facebook.com/bht.vazra                          \n"
		"    Find Manish @ facebook.com/manish.munikar               \n");

	while(getch() != ESC);
	main_menu();
}

void rules(void) {
	system("cls");
	print_heading();
	print_footer("Press [Esc] to goto Main Menu");

	gotoxy(0,5);
	printf("%s",
		"    RULES OF TIC-TAC-TOE                                      \n"
		"                                                              \n"
		"    1. Tic-tac-toe is two-player turn-wise game played on a   \n"
		"       board with 3x3 grid of squares                         \n"
		"    2. Two players are represented by 'x' and 'O'.            \n"
		"    3. Players place X/O alternatively until game ends.       \n"
		"    4. The player that draws 3-in-a-row wins.                 \n"
		"    5. If the board is filled without a winner, it's a tie.   \n");

	while (getch() != ESC);

	main_menu();
}

void highscores(int dif) {
// function to display the highscores of a particular difficult level
	int i, j;
	system("cls");
	print_heading();
	print_footer("Press [Esc] to goto Main Menu");
	gotoxy(0,5);



	FILE* file = NULL;
	file = fopen("scores.b", "r");
	if (file == NULL) {
		printf("    ERROR: Record file not found! ");
		getch(); main_menu();
	}

	int n = nelem(file, sizeof(RECORD));

	RECORD* data = malloc(n * sizeof(*data));

	rewind(file);
	fread(data, sizeof(*data), n, file);

	fclose(file);





	/*
	FILE *fp;
	fp = fopen("scores", "r"); // open the 'scores' file

	// if file not found, display an error message
	if (fp == NULL) {
		printf("    ERROR: Record file not found! ");
		getch(); main_menu();
	}

	int n = line_count(fp);  // number of lines (or entries) in the 'scores' file
	rewind(fp);		// bring the cursor back to the beginning of file (after counting the lines)

	// save all the lines of the file into an array and split each line with '|' into corresponding data[].name, data[].score, and data[].diff
	char line_str[n][35], name[31];
	int len, score;
	RECORD data[n]; // array of records
	int	i, j;
	for (i=0; i<n; i++) {
		fgets(line_str[i], sizeof(line_str[i]), fp); 	// get a line from the file
		len = strlen(line_str[i]);						// calculates the length of line
		line_str[i][len-1] = '\0'; 						// convert the last character of line_string from '\n' to '\0' (required)

		// split the line with '|' using string-token function
		strcpy(data[i].name, strtok(line_str[i], "|"));				// 1st part of line is name
		data[i].score = (int) strtol(strtok(NULL, "|"), NULL, 10);	// 2nd part of line is score
		data[i].diff = (int) strtol(strtok(NULL, "|"), NULL, 10);	// 3rd part of line is difficulty
	}

	fclose(fp); // close the file
	*/

	// sort the records in descending order of score
	for (i=0; i<n; i++) {
		for (j=i; j<n; j++)
			if (data[j].score > data[i].score)
				swap_record(&data[i], &data[j]);
	}

	// display the sorted list of top 10

	char d[7];
	strcpy(d, difficulty_str(dif));

	printf("    HIGHSCORES | %-9s  (Press [D] to change difficulty)\n\n", d);
	printf("      %4s %-25s %5s \n", "RANK", "NAME", "SCORE");
	printf("      ------------------------------------- \n");
	int count = 0;
	for (i=0; i<n && count<10; i++) {
		if (data[i].diff == dif) {
			printf("      %3d. %-25s %5d \n", count+1, data[i].name, data[i].score);
			++count;
		}
	}

	free(data);


	int c;
	while ((c=getch()) != ESC) {		 // if user presses ESC, goto main menu
		if (c=='d') {					// if user presses [D], then show highscores of another difficulty
			if (dif== 0) highscores(1);
			else if (dif==1) highscores(2);
			else if (dif==2) highscores(0);
		}
	}
	main_menu();
}

void multi_player(void) {
// the page when user selets 'Play against human'

	system("cls");
	print_heading();
	print_footer("Press [Esc] to goto Main Menu");
	gotoxy(0,5);

	char player[3][31]; // Player[0] will be O's name... player[-1+1]
						// player[2] will be X's name... player[ 1+1]

	// ask players' name, if invalid, goto previous screen
	printf("\n    Enter Player 'O' name: "); strin(player[0], sizeof(player[0]), stdin);
	if (strlen(player[0])<1) {
		printf("\n    INVALID NAME!"); getch(); play();
	}

	printf("\n    Enter Player 'X' name: "); strin(player[2], sizeof(player[2]), stdin);
	if (strlen(player[2]) < 1) {
		printf("\n    INVALID NAME!"); getch(); play();
	}

	// initialize turn randomly. Once initialized, the turn will alternate
	int turn_array[2]={-1, 1};
	int turn = turn_array[rand()%2];

	start_multiplayer(turn, player); // begin the multiplayer game

	while(getch() != ESC); // if the user presses [Esc], goto previous screen
	play();
}

void play(void) {
// the 'Play the game' page
	system("cls");
	print_heading();
	print_footer("Press [Esc] to goto Main Menu");

	gotoxy(0, 5);
	printf("%s",
		"    CHOOSE GAME MODE:                                          \n"
		"                                                               \n"
		"      [1] Play against computer (Single-Player)                \n"
		"      [2] Play against human    (Multi-Player)                 \n");

	char c = getch();
	switch (c) {
		case ESC: main_menu(); break;
		case '1': single_player(); break;
		case '2': multi_player(); break;
		default:  play(); break;
	}
}

void single_player(void) {
	system("cls");
	print_heading();
	print_footer("Press [Esc] to go back");

	// ask the player's name. The AI player's name will be "COMPUTER"
	char name[31], player[3][31];
	gotoxy(0,5); printf("    Enter your name: "); strin(name, sizeof(name), stdin);
	if (strlen(name)<1) {
		printf("\n    INVALID NAME");
		getch();
		play();
	}

	gotoxy(0,7); printf("%s", "    [1] Play with O \n"
							  "    [2] Play with X \n");
	int ask=1, c, human;
	while (ask==1 && (c=getch())) {
		if (c=='1') {
			human = -1;
			strcpy(player[0], name);
			strcpy(player[2], "COMPUTER");
			ask=0;
		}
		else if (c=='2') {
			human = 1;
			strcpy(player[0], "COMPUTER");
			strcpy(player[2], name);
			ask=0;
		}
		else if (c==ESC) play();
	}

	// initialize the turn randomly. Once initialized, the turn will alternate
	int turn_array[2]={1,-1};
	int init_turn = turn_array[rand() % 2];

	start_singleplayer(player, human, init_turn);

}

void how_to_play(void) {
	system("cls");
	print_heading();
	print_footer("Press [Esc] to goto Main Menu");

	gotoxy(0,5);
	printf("%s",
			"    HOW TO PLAY:                                            \n"
			"                                                            \n"
			"    Use number keys to select menus.                        \n"
			"                                                            \n"
			"    Use arrow keys to move cursor in the board              \n"
			"    and hit Enter to make the move                          \n");

	while (getch() != ESC);
	main_menu();
}
