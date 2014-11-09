#include "ttt.h"

void gotoxy(int x, int y) {
	COORD coord={0,0}; 		// center of axis is set to (0,0)
	coord.X=x;
	coord.Y=y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}

char ch(int i) {
	switch (i) {
		case 1: return 'X';
		case 0: return ' ';
		case -1: return 'O';
		default: return '\0';
	}
}

int line_count(FILE *file) {
// function to count the number of lines (records) in a file
	rewind(file);

	int n = 0;
	while(!feof(file))
		if (fgetc(file) == '\n') n++;
	return n;

	rewind(file);
}

void swap_record(RECORD *R1, RECORD *R2) {
	RECORD temp;
	temp = *R1;
	*R1 = *R2;
	*R2 = temp;
}

char* strin(char *str, int maxlen, FILE *file) {
// inputs the string (including spaces) upto \n and converts the last \n into \0, and stores it in a char*
	fgets(str, maxlen, file);
	int len = strlen(str);
	if (len>0 && str[len-1]=='\n')
		str[len-1] = '\0';
	return str;
}

int iswon(int d[9]) {
	// possible winning positions
	int wins[8][3] = { {0,1,2}, {3,4,5}, {6,7,8}, {0,3,6}, {1,4,7}, {2,5,8}, {0,4,8}, {2,4,6} };

	int i;
	for (i=0; i<8; i++) {
		if (d[wins[i][0]] != 0 && d[wins[i][1]] == d[wins[i][0]] && d[wins[i][2]] == d[wins[i][0]] )
			return d[wins[i][0]];
	}

	return 0;
}

int difficulty(void) {
	FILE *df = fopen("difficulty.b", "r");
	if (df == NULL) return 0;

	int d;
	fread(&d, sizeof(d), 1, df);
	fclose(df);

	if (d==1 || d==2) return d;
	return 0;
}

char *difficulty_str(int diff) {
	switch (diff) {
		case 0: return "Easy"; break;
		case 1: return "Medium"; break;
		case 2: return "Hard"; break;
		default: return NULL;
	}
}

void change_difficulty(void) {
	int diff = difficulty();

	switch (diff) {
		case 0: diff=1; break;
		case 1: diff=2; break;
		case 2: diff=0; break;
	}

	FILE *df = fopen("difficulty.b", "w");
	fwrite(&diff, sizeof(diff), 1, df);
	fclose(df);
}

int maximum(int a, int b) {
	int m = (a>b)? a:b;
	return m;
}

int minimum(int a, int b) {
	int m = (a<b)? a:b;
	return m;
}

int filled(int board[9]) {
	int full = 1;
	int i;
	for (i=0; i<9; i++)
		if (board[i] == 0) full = 0;

	return full;
}

int empty_board(int board[9]) {
	int emp = 1;
	int i;
	for (i=0; i<9; i++)
		if (board[i] != 0) emp = 0;

	return emp;
}

void save_record(char name[31], int score, int diff) {
	FILE *file = fopen("scores.b", "a");

	RECORD r;
	strcpy(r.name, name);
	r.score = score;
	r.diff = diff;

	fwrite(&r, sizeof(r), 1, file);

	fclose(file);
}

char* sCase(char *str, int c) {
	int i;
	for (i=0; i<strlen(str); i++) {
		if (isalpha(str[i])) {
			if (c==0)
				str[i] = tolower(str[i]);
			else if (c==1)
				str[i] = toupper(str[i]);
		}
	}

	return str;
}

int nelem(FILE* file, unsigned int elemsize) {
	rewind(file);

	char* pointer = malloc(elemsize * sizeof(*pointer));
	int count = 0;
	for (; fread(pointer, elemsize, 1, file); count++);

	free(pointer);
	rewind(file);
	return count;
}
