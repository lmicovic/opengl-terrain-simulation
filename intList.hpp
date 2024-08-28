
#ifndef INTLIST_H
#define INTLIST_H

#include <cstdlib>

typedef struct IntList {

    unsigned int value;
    IntList* next;

} IntList;

IntList* makeNode();


int sizeOfList(IntList* head);

// Add Value to the end List
IntList* addToList(IntList* head, int value);

unsigned int getNode(IntList* head, int i);

IntList* deleteList(IntList* head);

#endif // INTLIST_H
