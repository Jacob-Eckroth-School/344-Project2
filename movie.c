#include "movie.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
/*
** Description: Clears allocated memory from a movie pointer
** Prerequisites: moviePointer is allocated memory
** Updated/Returned: moviePointer is freed
*/
void clearMovieMemory(struct movie* moviePointer) {
	assert(moviePointer);

	free(moviePointer->title);
	for (int i = 0; i < moviePointer->amountOfLanguages; ++i) {
		free(moviePointer->languages[i]);

	}
	free(moviePointer->languages);
	free(moviePointer);
}

/*
** Description: Allocates memory for a movie pointer and assigns values based on passed string
** Prerequisites: fullLine is defined and in the correct format
** Updated/Returned: returns allocated memory pointer to movie
*/
struct movie* allocateMovie(char* fullLine) {
	struct movie* moviePointer = (struct movie*)malloc(sizeof(struct movie));

	char* savePointer;
	char* token = strtok_r(fullLine, ",", &savePointer);

	moviePointer->title = (char*)malloc((strlen(token) + 1) * sizeof(char));	//+1 because strlen doesn't include null
	strcpy(moviePointer->title, token);


	//year
	token = strtok_r(NULL, ",", &savePointer);
	moviePointer->year = atoi(token);

	//assigning languages
	token = strtok_r(NULL, ",", &savePointer);
	assignMovieLanguages(token, moviePointer);


	//rating
	token = strtok_r(NULL, "\n", &savePointer);
	moviePointer->rating = strtod(token, 0);
	return moviePointer;
}


/*
** Description: Sets the languages of a movie pointer based on passed string of languages in brackets
** Prerequisites: Language is in the right format i.e. [English,Spanish]
** Updated/Returned: sets the movie pointer languages to be an array of the languages.
*/
void assignMovieLanguages(char* languages, struct movie* moviePointer) {
	char* savePointer;

	
	char* token = strtok_r(languages, "[;]", &savePointer); //Assigns the first language
	int amountOfLanguages = 0;
	moviePointer->languages = (char**)malloc(sizeof(char*));		//allocates initial space for languages
	while (token) {

		++amountOfLanguages;
		moviePointer->languages = (char**)realloc(moviePointer->languages, (sizeof(char*) * amountOfLanguages)); //reallocates memory based on how many languages there are

		moviePointer->languages[amountOfLanguages - 1] = malloc((strlen(token) + 1) * sizeof(char));
		strcpy(moviePointer->languages[amountOfLanguages - 1], token);

		token = strtok_r(NULL, "[;]", &savePointer);
	}
	moviePointer->amountOfLanguages = amountOfLanguages;
}





