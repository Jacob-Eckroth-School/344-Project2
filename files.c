#include "files.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "typeDefs.h"

void processLargestFile() {
	char* fileName = findLargestFile();

}


void processSmallestFile() {

}




void processCustomFile() {


}




char* findLargestFile() {
	DIR* currDir = opendir(".");
	struct dirent* aDir;
	struct stat dirStat;

	char* largestFileTitle = NULL;
	int largestFileSize = 10;

	while ((aDir = readdir(currDir)) != NULL) {
		if (strncmp(PREFIX, aDir->d_name, strlen(PREFIX)) == 0) {
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
	closedir(currDir);
	printf("Largest File Title is: %s", largestFileTitle);
	free(largestFileTitle);
	return largestFileTitle;
}