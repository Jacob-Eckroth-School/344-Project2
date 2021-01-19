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
#include "linkedList.h"
#include "movie.h"
void processLargestFile() {
	char* fileName = findLargestFile();
	if (!fileName) {
		setRed();
		fprintf(stderr, "Could not find any files with the prefix: %s and suffix: %s\n",PREFIX,SUFFIX);
		resetColor();
		return;
	}
	printProcessingMessage(fileName);
	processFile(fileName);

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
	processFile(fileName);


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



void processFile(char* fileName) {
	int randomNumber = rand() % 100000;
	int numLength = getLengthOfNumber(randomNumber);
	
	char* directoryName = malloc(sizeof(char) * (numLength + strlen(fileName) + 1)); //plus one for null terminator
	
	char* numberString = malloc(sizeof(char) * (numLength + 1));
	sprintf(numberString, "%d", randomNumber);
	int index = 0;
	for (; index < strlen(DIRECTORYPREFIX); index++) {

		directoryName[index] = DIRECTORYPREFIX[index];
	}
	for (; index < strlen(DIRECTORYPREFIX) + numLength; index++) {
		directoryName[index] = numberString[index - strlen(DIRECTORYPREFIX)];
	}
	directoryName[index] = 0;
	free(numberString);



	mkdir(directoryName, DIRECTORYPERMISSIONS);
	
	dealWithFile(fileName, directoryName);
	
	free(directoryName);
}



void dealWithFile(char* fileName, char* directoryName) {
	struct linkedList* movieList = parseFile(fileName);
	sortListByYear(movieList);

	struct movie* traveller = movieList->head;
	int currentYear = traveller->year;


	char* filePath = makeFileName(directoryName,currentYear);
	
	FILE* currentFile = fopen(filePath, "w");
	while (traveller) {
		if (traveller->year != currentYear) {
			currentYear = traveller->year;
			free(filePath);
			fclose(currentFile);
			filePath = makeFileName(directoryName, currentYear);
			currentFile = fopen(filePath, "w");
		}

		fprintf(currentFile, "%s\n", traveller->title);
		traveller = traveller->next;
	}

	free(filePath);

	freeList(movieList);
}

struct linkedList* parseFile(char* fileName) {
	FILE* file = fopen(fileName, "r");
	char* line = NULL;
	size_t len = 0;
	ssize_t nread;

	//gets rid of the first line which is pointless.
	getline(&line, &len, file);
	struct linkedList* movieList = initializeList();
	struct movie* moviePointer;

	while ((nread = getline(&line, &len, file)) != -1) {		//goes through every line other than the first one
		moviePointer = allocateMovie(line);	//parses the line into the movie struct
		listAppend(movieList, moviePointer); //adds the movie struct to the linked list

	}
	free(line);
	fclose(file);
	return movieList;
}


char* makeFileName(char* directoryName, int year) {
	int numLength = getLengthOfNumber(year);
	char* fileName = malloc(sizeof(char) * (numLength + strlen(directoryName) + 6)); //plus six  for null terminator, .txt, and /

	char* numberString = malloc(sizeof(char) * (numLength + 1));
	sprintf(numberString, "%d", year);
	int index = 0;
	for (; index < strlen(directoryName); index++) {
		fileName[index] = directoryName[index];
	}
	fileName[index] = '/';
	index++;
	for (; index < strlen(directoryName) + numLength + 1; index++) {
		fileName[index] = numberString[index - strlen(directoryName) - 1];
	}
	int suffixIndex = 0;
	for (; index < strlen(directoryName) + numLength + 1 + strlen(NEWFILESUFFIX); ++index) {
	
		fileName[index] = NEWFILESUFFIX[suffixIndex];
		suffixIndex++;
	}
	
	fileName[index] = 0;

	printf("%s", fileName);

	free(numberString);
	return fileName;
}