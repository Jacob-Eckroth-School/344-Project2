#include "menus.h"
#include <stdio.h>
#include <stdbool.h>
#include "colors.h"
#include <string.h>
#include <stdlib.h>

/*
** Description: Prints the main menu
** Prerequisites: None
** Updated/Returned: None
*/
void printMainMenu() {
	printf("\n1. Select file to process\n2. Exit the program\nEnter a choice 1 or 2:");
}

/*
** Description: Prints the file choices
** Prerequisites: None
** Updated/Returned: None
*/
void printFileChoices() {
	printf("\nWhich file do you want to process?\nEnter 1 to pick the largest file\nEnter 2 to pick the smallest file\nEnter 3 to specify the name of a file\nEnter a choice from 1 to 3:");
}


/*
** Description: Gets a one digit input between lowLimt and highLimit from the user
** Prerequisites:  function passed is a void function that prints a prompt.
** Updated/Returned: returns an int between lowLimit and highLimit
*/
int getChoiceInput(int lowLimit, int highLimit, voidFunction promptFunction) {
	bool valid = false;
	int choice = 0;
	size_t bufsize = 2;
	char* userInput = (char*)malloc(bufsize * (sizeof(char)));
	while (!valid) {

		promptFunction();		//calls the function passed in by the previous function
		setCyan();
		
		getline(&userInput, &bufsize, stdin);
		if (userInput[strlen(userInput - 1) == 10]) {
			userInput[strlen(userInput) - 1] = 0; //getting rid of newline character left over from getline
		}
		resetColor();

		if (strlen(userInput) != 1) {

			valid = false;
		}
		else {
			//bounds checking
			if (userInput[0] - '0' >= lowLimit && userInput[0] - '0' <= highLimit) {
				choice = userInput[0] - '0';
				valid = true;
			}
			else {
				valid = false;
			}
		}

		if (!valid) {
			setRed();
			printError("You entered an incorrect choice. Try again.\n");
			resetColor();
		}
	}

	free(userInput);
	return choice;

}



