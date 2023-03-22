#include <stdio.h>

#ifndef DOUBLE_LINKED_LIST
#include "DoubleLinkedList.h"
#endif

void check_size(struct Node* start){
    int c = 0;
    if(start) c++;
    while(start->next){
        start = start->next;
        c++;
    }
    printf("actual size is %d\n",c);
}

void start_end_check(struct Node* start, struct Node* end){
    printf("\nstart_end_%d_%d\n",start->value, end->value);
}