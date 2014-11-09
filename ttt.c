#include "ttt.h"



int main(void) {
	loading(); // display the loading animation

	system("cls");
	system("COLOR F0"); // set black text on white background

	srand(time(NULL)); // seed the randomizer

	main_menu(); // show the main menu

	return 0;
}

