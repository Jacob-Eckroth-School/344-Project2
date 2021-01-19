#include <stdio.h>


/*
** Description: Resets console color to default color
** Prerequisites: None
** Updated/Returned: Sets console color to default
*/
void resetColor() {
	printf("\033[0m");
}


/*
** Description: Prints a message in red text
** Prerequisites: Message is allocated
** Updated/Returned: Message is printed in red
*/
void printError(char* errorMessage) {
	printf("\033[0;31m%s", errorMessage);
	resetColor();
}

/*
** Description: Sets console color to red
** Prerequisites: None
** Updated/Returned: None
*/
void setRed() {
	printf("\033[0;31m");
}

/*
** Description: Sets console color to green
** Prerequisites: None
** Updated/Returned: None
*/
void setGreen() {
	printf("\033[0;32m");
}

/*
** Description: Sets console color to cyan
** Prerequisites: None
** Updated/Returned: None
*/
void setCyan() {
	printf("\033[0;36m");
}