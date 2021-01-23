/*
Name: Jacob Eckroth
Date: 1/25/2021
Project Name: Assignment 2: Files & Directories
Description: Takes input in from a user for a file. Creates a new directory with the format
* eckrothj.movies.* where * is a number between 0-99999. In that directory, for each year choice in the movie file
* creates a new .txt file called year.txt where year is the year, and puts the titles of all the movies
* that were recorded as released in that year from the original file.
*/

#include "menus.h"
#include "files.h"
#include <stdbool.h>
#include "typeDefs.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>




/*
** Description: Main FUnction
** Prerequisites: None
** Updated/Returned: returns 0 (hopefully)
*/
int main() {
	time_t t;
	srand((unsigned) time(&t));
	bool running = true;

	int choice = 0;	

	//main run loop, runs until user makes it stop
	while (running) {
		voidFunction mainMenu = &printMainMenu;

		//gets choice from user on what they want to do in the main menu
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
