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
#include <assert.h>

#include "typeDefs.h"
#include "colors.h"
#include "usefulFunctions.h"
#include "linkedList.h"
#include "movie.h"
#include "menus.h"

/*
** Description: Processes and creates all the directories and files for the largest filesize in the directory
** Prerequisites: None
** Updated/Returned: Creates a new directory if the file is found, otherwise breaks out and lets user rechoose.
*/
void processLargestFile() {
	char* fileName = findLargestFile();

	//if there is no valid file
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

/*
** Description: Processes and creates all the directories and files for the smallest filesize in the directory
** Prerequisites: None
** Updated/Returned: Creates a new directory if the file is found, otherwise breaks out and lets user rechoose.
*/
void processSmallestFile() {
	char* fileName = findSmallestFile();

	//if there is no valid file
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

/*
** Description: Prints a processing message for a given filename. 
** Prerequisites: fileName is allocated correctly.
** Updated/Returned: Prints the processing message.
*/
void printProcessingMessage(char* fileName) {
	assert(fileName);
	setGreen();
	printf("\nNow processing the chosen file named %s\n", fileName);
	resetColor();
}


/*
** Description: Processes a file entered by the user
** Prerequisites: None
** Updated/Returned: Creates updated directory if file exists, otherwise nothing really happens
*/
void processCustomFile() {
	char* input = getUserStringInput("Enter the complete file name: ", 0);
	bool failed = true;
	if (access(input, F_OK) == 0) {			//if the file exists
		if (is_regular_file(input)) {		//if the file isn't a directory (fails on other things though)
			failed = false;
			printProcessingMessage(input);
			processFile(input);
		}

	}
	
	if (failed) {
		setRed();
		fprintf(stderr, "\nThe file %s was not found. Try again\n", input);
		resetColor();
	}
	free(input);
	if (failed) {
		userSelectFile();
	}

}



/*
** Description: Finds the name of the largest file in the directory with a given suffix and prefix
** Prerequisites: None
** Updated/Returned: Returns a pointer to the name of the largest file in the directory on the heap.
** Returns null if no file is found
*/
char* findLargestFile() {

	DIR* currDir = opendir(".");
	struct dirent* aDir;
	struct stat dirStat;

	char* largestFileTitle = NULL;
	int largestFileSize = 0;

	//looping through every entry in the directory
	while ((aDir = readdir(currDir)) != NULL) {

		//checking the prefix
		if (strncmp(PREFIX, aDir->d_name, strlen(PREFIX)) == 0) {
			//checking the suffix
			if (checkSuffix(SUFFIX, aDir->d_name)) {
				stat(aDir->d_name, &dirStat);
				//if the file isn't a directory
				if(S_ISREG(dirStat.st_mode)){
					//if the file size is greater than our currently stored size
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
	}
	closedir(currDir);
	
	return largestFileTitle;
}


/*
** Description: Finds the name of the smallest file in the directory with a given suffix and prefix
** Prerequisites: None
** Updated/Returned: Returns a pointer to the name of the smallest file in the directory on the heap.
** Returns null if no file is found
*/
char* findSmallestFile() {
	DIR* currDir = opendir(".");
	struct dirent* aDir;
	struct stat dirStat;

	char* smallestFileTitle = NULL;
	int smallestFileSize = INT_MAX;

	//loops through every entry in the directory
	while ((aDir = readdir(currDir)) != NULL) {

		if (strncmp(PREFIX, aDir->d_name, strlen(PREFIX)) == 0) {		//checking the prefix
			if (checkSuffix(SUFFIX, aDir->d_name)) {					//checking the suffix
				stat(aDir->d_name, &dirStat);
				if(S_ISREG(dirStat.st_mode)){							//checking that it isn't a directory
					if (dirStat.st_size <= smallestFileSize) {			//if the size is smaller than our current size
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
	}
	closedir(currDir);
	
	return smallestFileTitle;
}


/*
** Description: Uses information from inside a file to create a directory and fill it with txt files based on the file
** Prerequisites: fileName exists and is allocated
** Updated/Returned: No returns, new directory and files are created and filled with appropriate data. 
*/
void processFile(char* fileName) {
	assert(fileName);

	
	int randomNumber = rand() % 100000;
	int numLength = getLengthOfNumber(randomNumber);
	

	//creating the directory name
	char* directoryName = malloc(sizeof(char) * (numLength + strlen(fileName) + 1)); //plus one for null terminator
	char* numberString = malloc(sizeof(char) * (numLength + 1));
	sprintf(numberString, "%d", randomNumber);
	int index = 0;
	//filling in the prefix of the directory name
	for (; index < strlen(DIRECTORYPREFIX); index++) {

		directoryName[index] = DIRECTORYPREFIX[index];
	}
	//filling in the random number part of the directory name
	for (; index < strlen(DIRECTORYPREFIX) + numLength; index++) {
		directoryName[index] = numberString[index - strlen(DIRECTORYPREFIX)];
	}
	directoryName[index] = 0;
	free(numberString);

	//makes the new directory
	mkdir(directoryName, DIRECTORYPERMISSIONS);
	
	printDirectoryInfo(directoryName);

	dealWithFile(fileName, directoryName);
	
	free(directoryName);
}


/*
** Description: Prints the name of the directory created
** Prerequisites: direcotyrName exists and is allocated
** Updated/Returned: None. Prints info.
*/
void printDirectoryInfo(char* directoryName) {
	assert(directoryName);
	setGreen();
	printf("Created directory with name %s\n", directoryName);

	resetColor();
}


/*
** Description: Fills a directory full of movie txt files and names based on the file passed to it. 
** Prerequisites: directoryName and fileName are allocated and both exist.
** Updated/Returned: Directory is filled with files based on movie list. 
*/
void dealWithFile(char* fileName, char* directoryName) {

	struct linkedList* movieList = parseFile(fileName);
	
	sortListByYear(movieList);

	struct movie* traveller = movieList->head;
	int currentYear = traveller->year;

	char* filePath = makeFileName(directoryName,currentYear);
	
	FILE* currentFile = fopen(filePath, "w");

	//Loops through all the movies in the sorted linked list.
	while (traveller) {
		if (traveller->year != currentYear) {   //if we're at a new year we need to close our current file and make a new one
			currentYear = traveller->year;
			free(filePath);
			fclose(currentFile);
			filePath = makeFileName(directoryName, currentYear);
			currentFile = fopen(filePath, "w");
		}

		fprintf(currentFile, "%s\n", traveller->title);	
		traveller = traveller->next;
		chmod(filePath, FILEPERMISSIONS);				//sets custom permissions for the file
	}

	fclose(currentFile);

	free(filePath);
	freeList(movieList);
}


/*
** Description: Takes a file that is formatted correctly and parses all the movies out of it and returns a linked list of the movies
** Prerequisites: fileName exists and is allocated and there is a file of that name.
** Updated/Returned: linked list is allocated with all the movies in the original file. 
*/
struct linkedList* parseFile(char* fileName) {
	FILE* file = fopen(fileName, "r");
	assert(file);

	char* line = NULL;
	size_t len = 0;
	ssize_t nread;
	getline(&line, &len, file);						//gets rid of the initial line which is useless
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

/*
** Description: creates a file name based on the directory name and the year chosen for th efile
** Prerequisites: directoryName is allocated, year is a number.
** Updated/Returned: returns a pointer to the new fileName with directory prefix.
*/
char* makeFileName(const char* directoryName, int year) {
	assert(directoryName);

	int numLength = getLengthOfNumber(year);
	char* fileName = malloc(sizeof(char) * (numLength + strlen(directoryName) + 6)); //plus six  for null terminator, .txt, and '/'

	char* numberString = malloc(sizeof(char) * (numLength + 1));
	sprintf(numberString, "%d", year);
	int index = 0;

	//adding directory name to fileName
	for (; index < strlen(directoryName); index++) {
		fileName[index] = directoryName[index];
	}
	fileName[index] = '/';
	index++;

	//adding the year to the fileName
	for (; index < strlen(directoryName) + numLength + 1; index++) {
		fileName[index] = numberString[index - strlen(directoryName) - 1];
	}
	int suffixIndex = 0;
	//adding the suffix to the fileName
	for (; index < strlen(directoryName) + numLength + 1 + strlen(NEWFILESUFFIX); ++index) {
	
		fileName[index] = NEWFILESUFFIX[suffixIndex];
		suffixIndex++;
	}
	
	fileName[index] = 0;
	free(numberString);
	return fileName;
}


/*
** Description: Prints the choices for the program, and gets valid input from the user on what they want to do with files
** Prerequisites: None.
** Updated/Returned: Processes file based on user choice
*/
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
