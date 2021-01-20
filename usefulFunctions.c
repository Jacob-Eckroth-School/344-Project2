#include "usefulFunctions.h"
#include <string.h>
#include <assert.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "colors.h"
#include "typeDefs.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

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
	char* input;
        if(bufSize!=0){
		input = (char*)malloc(bufsize * (sizeof(char)));
	}
	printf("%s",prompt);
	setCyan();
	getline(&input, &bufsize, stdin);
	if(DEBUG){
		printf("Full Dec of inputted string: ");
		for(int i = 0; i < strlen(input); i++){
			printf("%d ",input[i]);
		}
		printf("\n");
	}
	if (input[strlen(input) - 1] == 10) {
		input[strlen(input) - 1] = 0; //getting rid of newline character left over from getline
	}

	resetColor();

	return input;
}


int is_regular_file(const char* fileName) {
	struct stat path_stat;
	stat(fileName, &path_stat);
	return S_ISREG(path_stat.st_mode);
}