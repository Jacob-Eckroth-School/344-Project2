
#include "linkedList.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include "colors.h"

/*
** Description: Appends a movie pointer to a linked list
** Prerequisites: list and moviePointer are allocated
** Updated/Returned: linked list is updated to have the movie pointer at the end
*/
void listAppend(struct linkedList* list, struct movie* moviePointer) {
	assert(list);
	//if the list head exists
	if (list->head) {
		list->tail->next = moviePointer;
		list->tail = moviePointer;
	}
	//else if the list has no items in it.
	else {
		list->head = moviePointer;
		list->tail = moviePointer;
	}
	(list->amountOfMovies)++;
}


/*
** Description: Initializes and returns a pointer to a linked list
** Prerequisites: none
** Updated/Returned: Returns an empty linked list.
*/
struct linkedList* initializeList() {
	struct linkedList* list = (struct linkedList*)malloc(sizeof(struct linkedList));
	list->head = NULL;
	list->tail = NULL;
	list->amountOfMovies = 0;
	return list;
}



/*
** Description: Frees all memory associated with a linked list
** Prerequisites: linked list is allocated
** Updated/Returned: memory of linked list is freed
*/
void freeList(struct linkedList* list) {
	assert(list);
	struct movie* traveler = list->head;
	struct movie* travelerNext = list->head->next;


	//frees every movie in the linked list
	while (traveler) {
		assert(traveler);
		clearMovieMemory(traveler);
		traveler = travelerNext;
		if (traveler) {
			travelerNext = traveler->next;
		}
	}
	free(list);
}



void printList(struct linkedList* list){
	struct movie* traveller = list->head;
	while (traveller) {
		printf("%s %d %.2f\n", traveller->title, traveller->year, traveller->rating);
		traveller = traveller->next;
	}
}


void resetTail(struct linkedList* list) {
	struct movie* traveller = list->head;
	while (traveller->next != NULL) {
		traveller = traveller->next;
	}
	list->tail = traveller;
}


void sortListByYear(struct linkedList* list) {
	assert(list);
	list->head = merge_sort_ascending(list->head, list->amountOfMovies);
	resetTail(list);

	
}


//taken from CS162 final project. In place merge sort.
struct movie* merge_sort_ascending(struct movie* head, int length) {
	
	if (length == 1) {//it's sorted!

		return head;
	}
	int left_length = length / 2; //left length will be the smaller one
	int right_length = length - left_length; //makes sure the right length and the left length add up to the total.

	struct movie* left = head; //the head to the left node is just the start of the list.

	for (int i = 0; i < left_length - 1; i++) {

		head = head->next; //we can change head since we already kept track of it in the left.
	}

	struct movie* right = head->next; //sets the right node.
	head->next = NULL;//breaking chain


	left = merge_sort_ascending(left, left_length);//sorts the left list.
	right = merge_sort_ascending(right, right_length);//sorts the right list.

	return merge_lists(left, right);//returns the two lists combined.
}

struct movie* merge_lists(struct movie* left, struct movie* right) {


	struct movie* new_node = NULL;
	struct movie* temp = NULL;
	while (left != NULL && right != NULL) {//while we're not at the end of either list.

		if (new_node == NULL) { //if it's the first node in the list we need to change the head.
			if (left->year < right->year) {
				new_node = left;
				temp = new_node;
				left = left->next;
			}
			else {
				new_node = right;
				temp = new_node;
				right = right->next;
			}
		}
		else { //if we're past the first node and don't need to care about the head anymore.
			if (left->year < right->year) {
				temp->next = left;
				temp = temp->next;
				left = left->next;
			}
			else {
				temp->next = right;
				temp = temp->next;
				right = right->next;
			}

		}
	}
	if (left == NULL) { //Whichever list we reached the end of first, we point the last element of temp to the rest of the other list.
		temp->next = right;
	}
	else {
		temp->next = left;
	}
	return new_node; //return the head to the merged list.
}