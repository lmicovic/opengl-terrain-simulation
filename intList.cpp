#include <cstdlib>
#include "intList.hpp"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>



int sizeOfList(IntList* head) {

    if(head == NULL) {
        return 0;
    }

    IntList* tmp = head;

    int c = 0;
    while(tmp != NULL) {
        tmp = tmp->next;
        c++;
    }

    return c;

}

// Add Value to the end List
IntList* addToList(IntList* head, int value) {



    IntList* tmp = (IntList*) malloc(sizeof(IntList));

    tmp->value = value;
    tmp->next = NULL;



    if(head == NULL) {
        head = tmp;
        return head;
    }



    IntList* p;

    p = head;
    while(p->next != NULL) {
        p = p->next;
    }

    p->next = tmp;

    return head;
}

IntList* deleteList(IntList* head) {

    IntList* current;
    current = head;

    IntList* next;

    while (current != NULL)
    {
        next = current->next;
        free(current);
        current = next;
    }

    /* deref head_ref to affect the real head back
        in the caller. */
    head = NULL;

    return head;

}


unsigned int getNode(IntList* head, int i) {

    int listSize = sizeOfList(head);
    // std::cout << listSize << " " << i << std::endl;
    if(listSize <= i) {
        std::cout << "Index out of bound - List Size " << listSize << " - index " << i << std::endl;
        exit(0);
    }

    IntList* tmp = head;
    int c = 0;
    while(i-- >= 0 && tmp->next != NULL) {


        tmp = tmp->next;

        c++;


    }

    return tmp->value;
}
