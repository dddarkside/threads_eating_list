#include "DoubleLinkedList.h"


#define DEBUG

#ifndef DEBUG
#define VAL rand()%RAND_LIM
#endif

#ifdef DEBUG
int j = 0;//
#define VAL ++j
#endif


void fill_node(struct Node** current){
    (*current)->next->prev = *current;
    (*current) = (*current)->next;
    (*current)->value = VAL;//rand()%RAND_LIM;
}


struct Node* list_init(int size){

    // Initialization of first signal Node:
    struct Node* start;
    if(!(start = (struct Node*)malloc(sizeof(struct Node)) ) ){
        strerror(ENOMEM);
        return 0;
    }
    start->value = 0; //  first always 0
    struct Node* current = start;

    // Cycled making nodes:
    for(int i=0;i<size+1;++i){ //+1 for finish signal
        if(!(current->next = malloc(sizeof(struct Node)) ) ){
            strerror(ENOMEM);
            return 0;
        }
        fill_node(&current);
    }
    current->value = INT_MAX; // endNode - always INT_MAX

    return start;
}

struct Node* find_end(struct Node* start){
    struct Node* current = start;
    while(current->next) current = current->next;
    return current;
}
