#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <pthread.h>
#include "DoubleLinkedList.h"


#define MANTISSA 23


int     count_ones(int num);
int     count_zeros(int num);
uint8_t check_space(struct Node* current, uint8_t mode);
void    move_forward(struct Node** current);
void    move_back(struct Node** current);
uint8_t safe_move(struct Node** current, uint8_t mode);
void*   eater(void* arg);