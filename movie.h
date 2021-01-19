#ifndef MOVIE
#define MOVIE



struct movie {
	char* title;
	int year;
	char** languages;
	int amountOfLanguages;
	double rating;
	struct movie* next;
};


void clearMovieMemory(struct movie*);
struct movie* allocateMovie(char*);
void assignMovieLanguages(char* languages, struct movie* moviePointer);

#endif