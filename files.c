#include "files.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

#include "typeDefs.h"
#include "colors.h"
#include "usefulFunctions.h"
void processLargestFile() {
	char* fileName = findLargestFile();
	if (!fileName) {
		setRed();
		fprintf(stderr, "Could not find any files with the prefix: %s and suffix: %s\n",PREFIX,SUFFIX);
		resetColor();
		return;
	}
	printProcessingMessage(fileName);

	free(fileName);
}


void processSmallestFile() {
	char* fileName = findSmallestFile();
	if (!fileName) {
		setRed();
		fprintf(stderr, "Could not find any files with the prefix: %s and suffix: %s\n", PREFIX, SUFFIX);
		resetColor();
		return;
	}
	printProcessingMessage(fileName);




	free(fileName);
}


void printProcessingMessage(char* fileName) {
	setGreen();
	printf("\nNow processing the chosen file named %s\n", fileName);
	resetColor();
}



void processCustomFile() {


}




char* findLargestFile() {
	DIR* currDir = opendir(".");
	struct dirent* aDir;
	struct stat dirStat;

	char* largestFileTitle = NULL;
	int largestFileSize = 0;

	while ((aDir = readdir(currDir)) != NULL) {
		if (strncmp(PREFIX, aDir->d_name, strlen(PREFIX)) == 0) {
			if (checkSuffix(SUFFIX, aDir->d_name)) {
				stat(aDir->d_name, &dirStat);
				if (dirStat.st_size >= largestFileSize) {
					largestFileSize = dirStat.st_size;
					if (largestFileTitle) {
						free(largestFileTitle);
					}
					largestFileTitle = malloc(sizeof(char) * (strlen(aDir->d_name) + 1));
					strcpy(largestFileTitle, aDir->d_name);

				}
			}

		}
	}
	closedir(currDir);

	return largestFileTitle;
}



char* findSmallestFile() {
	DIR* currDir = opendir(".");
	struct dirent* aDir;
	struct stat dirStat;

	char* smallestFileTitle = NULL;
	int smallestFileSize = INT_MAX;

	while ((aDir = readdir(currDir)) != NULL) {
		if (strncmp(PREFIX, aDir->d_name, strlen(PREFIX)) == 0) {
			if (checkSuffix(SUFFIX, aDir->d_name)) {
				stat(aDir->d_name, &dirStat);
				if (dirStat.st_size <= smallestFileSize) {
					smallestFileSize = dirStat.st_size;
					if (smallestFileTitle) {
						free(smallestFileTitle);
					}
					smallestFileTitle = malloc(sizeof(char) * (strlen(aDir->d_name) + 1));
					strcpy(smallestFileTitle, aDir->d_name);

				}
			}

		}
	}
	closedir(currDir);

	return smallestFileTitle;
}