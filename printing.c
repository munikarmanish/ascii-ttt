#include "ttt.h"

void print_heading(void) {
	gotoxy(0, 2);
	printf("%s",
		"    TIC-TAC-TOE                           by MANISH & BRIHAT    \n"
		"  ============================================================  \n");
}

void print_footer(char* str) { gotoxy(0, 21); printf("  ------------------------------------------------------------ ");
	gotoxy(0, 22); printf("    %-50s %5s", str, "M&B");
}

void print_board(int x, int y, int d[9]) {
	gotoxy(x, y+0); printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", ' ',' ',' ',' ',' ',VCH,' ',' ',' ',' ',' ',VCH,' ',' ',' ',' ',' ');
	gotoxy(x, y+1); printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", ' ',' ',ch(d[0]),' ',' ',VCH,' ',' ',ch(d[1]),' ',' ',VCH,' ',' ',ch(d[2]),' ',' ');
	gotoxy(x, y+2); printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", ' ',' ',' ',' ',' ',VCH,' ',' ',' ',' ',' ',VCH,' ',' ',' ',' ',' ');
	gotoxy(x, y+3); printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", HCH,HCH,HCH,HCH,HCH,CCH,HCH,HCH,HCH,HCH,HCH,CCH,HCH,HCH,HCH,HCH,HCH);
	gotoxy(x, y+4); printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", ' ',' ',' ',' ',' ',VCH,' ',' ',' ',' ',' ',VCH,' ',' ',' ',' ',' ');
	gotoxy(x, y+5); printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", ' ',' ',ch(d[3]),' ',' ',VCH,' ',' ',ch(d[4]),' ',' ',VCH,' ',' ',ch(d[5]),' ',' ');
	gotoxy(x, y+6); printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", ' ',' ',' ',' ',' ',VCH,' ',' ',' ',' ',' ',VCH,' ',' ',' ',' ',' ');
	gotoxy(x, y+7); printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", HCH,HCH,HCH,HCH,HCH,CCH,HCH,HCH,HCH,HCH,HCH,CCH,HCH,HCH,HCH,HCH,HCH);
	gotoxy(x, y+8); printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", ' ',' ',' ',' ',' ',VCH,' ',' ',' ',' ',' ',VCH,' ',' ',' ',' ',' ');
	gotoxy(x, y+9); printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", ' ',' ',ch(d[6]),' ',' ',VCH,' ',' ',ch(d[7]),' ',' ',VCH,' ',' ',ch(d[8]),' ',' ');
	gotoxy(x, y+10); printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", ' ',' ',' ',' ',' ',VCH,' ',' ',' ',' ',' ',VCH,' ',' ',' ',' ',' ');
	printf("\n\n");
}

void status(char player[3][31], int wins[3], int draws) {
	system("cls");
	print_heading();
	print_footer("Press [Esc] to goto Main Menu");

	gotoxy(0,5);
	printf("    LAST GAME STATUS: \n\n");
	printf("      %-20s : %3d \n", player[0], wins[0]);
	printf("      %-20s : %3d \n", player[2], wins[2]);
	printf("      %-20s : %3d \n", "DRAWS", draws);

	while (getch() != ESC);
	main_menu();
}

void loading(void) {
	system("COLOR 0F");

	int step = 10;

	int i,j;
	for (i=0; i<10; i++) {
		for (j=0; j<50000000; j++); // delay one second

		system("cls");
		gotoxy(20,9); printf("Loading...     %3d%c", step*(i+1), '%');

		for (j=0; j<10; j++) {
			gotoxy(20+j*2, 11); printf("%c%c", 196, 196);
		}

		for (j=0; j<=i; j++) {
			gotoxy(20+j*2, 11); printf("%c%c", 219, 219);
		}
	}

	for (i=0; i<100000000; i++);
	system("cls");
	gotoxy(20,9); printf("Press any key...");
	getch();
}
