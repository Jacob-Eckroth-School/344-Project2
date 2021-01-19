#include "usefulFunctions.h"
#include <string.h>
#include <assert.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "colors.h"



bool checkSuffix(char* suffix, char* stringToCheckAgainst) {
	assert(suffix); 
	assert(stringToCheckAgainst);

	//if the string is longer than the actual string yaknow.
	if (strlen(stringToCheckAgainst) < strlen(suffix)) {
		return false;
	}

	int suffixLength = strlen(suffix);
	int stringLength = strlen(stringToCheckAgainst);
	for (int i = 0; i < strlen(suffix); i++) {
		if (stringToCheckAgainst[stringLength - 1 - i] != suffix[suffixLength - 1 - i]) {
			return false;
		}
	}
	return true;

}



int getLengthOfNumber(int number) {
	return (number == 0) ? 1 : floor(log10(abs(number))) + 1;
}

char* getUserStringInput(char* prompt, int bufSize) {
	size_t bufsize = bufSize;
	char* input = (char*)malloc(bufsize * (sizeof(char)));
	printf("%s",prompt);
	setCyan();
	getline(&input, &bufsize, stdin);
	if (input[strlen(input) - 1] == 10) {
		input[strlen(input) - 1] = 0; //getting rid of newline character left over from getline
	}

	resetColor();

	return input;
}