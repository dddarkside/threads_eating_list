#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include "stdio.h"
#include <limits.h>

#define RAND_LIM 1024
#define DOUBLE_LINKED_LIST

struct Node{
    struct Node* prev;
    int value;
    struct Node* next;
};

void fill_node(struct Node** current);
struct Node* list_init(int size);
struct Node* find_end(struct Node* start);