#include "usefulFunctions.h"
#include <string.h>





bool checkSuffix(char* suffix, char* stringToCheckAgainst) {


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