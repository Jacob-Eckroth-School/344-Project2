#ifndef FILES
#define FILES
#include "linkedList.h"

void processLargestFile();
void processSmallestFile();
void processCustomFile();
char* findLargestFile();
char* findSmallestFile();


void processFile(char* fileName);

void printProcessingMessage(char*);

void dealWithFile(char*, char*);

struct linkedList* parseFile(char*);

char* makeFileName(char*, int);

#endif