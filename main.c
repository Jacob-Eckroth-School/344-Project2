/*
Name: Jacob Eckroth
Date: 1/25/2021
Project Name: Assignment 2: Files & Directories
Description:
*/

#include "menus.h"
#include "files.h"
#include <stdbool.h>
#include "typeDefs.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


void userSelectFile();


int main() {
	time_t t;
	srand((unsigned) time(&t));

	bool running = true;
	


	int choice = 0;
	while (running) {
		voidFunction mainMenu = &printMainMenu;
		choice = getChoiceInput(1, 2, mainMenu);
		if (choice == 2) {
			running = false;
		}
		else {
			userSelectFile();
		}

	}

	return 0;

}

void userSelectFile() {
	voidFunction fileMenu = &printFileChoices;
	int choice = getChoiceInput(1, 3, fileMenu);
	switch (choice) {
	case 1:
		processLargestFile();

		break;
	case 2:

		processSmallestFile();
		break;
	case 3:

		processCustomFile();
		break;
	default:
		printf("Error in userSelect switch statement\n");
		break;
	}
}
