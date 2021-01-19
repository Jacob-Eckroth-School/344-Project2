#include "usefulFunctions.h"
#include <string.h>
#include <assert.h>
#include <math.h>
#include <stdlib.h>



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