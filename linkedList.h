#ifndef LINKEDLIST
#define LINKEDLIST
#include "movie.h"
struct linkedList {
	struct movie* head;
	int amountOfMovies;
	struct movie* tail;
};

void listAppend(struct linkedList* list, struct movie*);
struct linkedList* initializeList();



void freeList(struct linkedList* list);



void resetTail(struct linkedList* list);

void printList(struct linkedList* list);

void sortListByYear(struct linkedList* list);
struct movie* merge_sort_ascending(struct movie*, int);
struct movie* merge_lists(struct movie*, struct movie*);


#endif