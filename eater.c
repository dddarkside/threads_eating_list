#include "eater.h"
#define NOT_DEBUG

extern pthread_mutex_t eaters_mutex;


int count_ones(int num){
    int counter = 0;
    while(num){
        if(num%2 != 0) counter++;
        num /= 2;
    }
    return counter;
}


int count_zeros(int num){
    return MANTISSA - count_ones(num); //  All non one bits - zeros
}


uint8_t check_space(struct Node* current, uint8_t mode){
    //  This function checks that thread still have space to work
    //  Data race excluded by checking 2 next Nodes
    if(mode) {
        if (current->prev)
            if(current->prev->prev) return 1;
        return 0;
    }
    if(current->next)
        if( current->next->next) return 1;
    return 0;
}


void move_forward(struct Node** current){
    *current = (*current)->next;
    free((*current)->prev);
    (*current)->prev = NULL;
}


void move_back(struct Node** current){
    *current = (*current)->prev;
    free((*current)->next);
    (*current)->next = NULL;
}


uint8_t safe_move(struct Node** current, uint8_t mode){
    // This function checks that the thread can take a new Node
    // and than safely takes it.
    // If operation done - returns 1, else - returns 0
    pthread_mutex_lock(&eaters_mutex);

    uint8_t res = check_space(*current, mode);

    if(res){
        if(mode)move_back(current);
        else move_forward(current);
    }
    else {
        if(mode)
        {//Check "next" because second thread can't talk with "next" elem because it freed
            if (current[0]->prev) current[0]->prev->next = NULL;
        }
        else
        {
            if (current[0]->next)current[0]->next->prev = NULL;
        }
        free(current[0]);//  Free up memory if it's the end
    }

    pthread_mutex_unlock(&eaters_mutex);
    return res;
}


void* eater(void* arg){
    uint8_t no_stop;  // stop signal
    uint8_t mode = 0; // 0 - from start, 1 - from end
    int elems_c = 0;  // counts elems of list
    int digits_c = 0; // counts number of zeros or ones depending on the mode
    struct Node* current = (struct Node*)arg; // pointer for using Nodes

    if(current->value)mode = 1; // checking mode: 0 - start/ 1 - end

    no_stop = safe_move(&current, mode);
    // !Don't count special signal as element

    // Main cycle:
    while(no_stop){

        //Right:
        if(mode) digits_c += count_ones(current->value);
        //Left:
        else     digits_c += count_zeros(current->value);

        no_stop = safe_move(&current, mode);
        elems_c++;
    }

    if(mode)printf("Quantity of ones:%d , Elements checked:%d\n",digits_c,elems_c);
    else printf("Quantity of zeros:%d , Elements checked:%d\n",digits_c,elems_c);
}