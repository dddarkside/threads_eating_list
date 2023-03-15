#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include <semaphore.h>
#include <stdint.h>

#define NDEBUG
#define DEFAULT_SIZE 100000
#define RAND_LIM 1024

struct list{
    struct list* prev;
    int value;
    struct list* next;
};

pthread_mutex_t mutex;
int global_size;

int count_ones(int num){
    int counter = 0;
    while(num){
        if(num%2 != 0) counter++;
        num /= 2;
    }
    return counter;
}

int count_zeros(int num){
    int counter = 0;
    while(num){
        if(num%2 == 0) counter++;
        num /= 2;
    }
    return counter;
}

void* eater(void* arg){
    uint8_t mode = 1;  // 0 - from start, 1 - from end
    int elems_c = 0;   // counts elems of list
    int digits_c = 0;  // counts number of zeros or ones depending on the mode
    int stop = 1;      // stop signal(if 0)
    struct list* current = (struct list*)arg;

    if(!(current->prev)) mode = 0; // checking mode 0 - start/ 1 - end

    pthread_mutex_lock(&mutex);
    stop = global_size--;
    pthread_mutex_unlock(&mutex);

    while(stop){

#ifdef DEBUG
        printf("stop:%d mode:%d\n",stop,mode);
#endif

        if(mode){  // right thread
            digits_c += count_ones(current->value);
            if(current->prev){  // if we can go
                current = current->prev;
                free(current->next);
                current->next = NULL;
            }
            else {
                free(current);
                current = NULL;
                elems_c++;
                break;
            }
        }
        else{  // left thread
            digits_c += count_zeros(current->value);
            if(current->next){  // if we can go
                current = current->next;
                free(current->prev);
                current->prev = NULL;
            }
            else {
                free(current);
                current = NULL;
                elems_c++;
                break;
            }

        }
        elems_c++;

        pthread_mutex_lock(&mutex);
        stop = global_size--;
        pthread_mutex_unlock(&mutex);
        if(stop==-1)stop=0;
    }
    pthread_mutex_lock(&mutex);
    global_size = 0;
    pthread_mutex_unlock(&mutex);

    if(mode)printf("Quantity of ones:%d , Elements checked:%d\n",digits_c,elems_c);
    else printf("Quantity of zeros:%d , Elements checked:%d\n",digits_c,elems_c);
}


void error(int key){
	if(!key)printf("ERROR: There is not numeric argument for size");
	else if(key)printf("ERROR: memory allocation has been failed");
    //  "else if" not "else" for the future
}


int main(int argc, char* argv[]) {
    // Choosing size of list:
    global_size = DEFAULT_SIZE;
    if(argc>1) {
        global_size = strtoul(argv[1],NULL,10);
        if(!global_size){
            error(0);
            return -20022002; //  Check that not char
        }
        if(global_size > INT_MAX-1) global_size = DEFAULT_SIZE; // check that not long
    }

    // Making random list:
    srand(time(NULL));
    struct list* field;
    if(!(field = (struct list*)malloc(sizeof(struct list)))){
        error(1);
        return -20022002;
    }
    struct list* current = field;
    current->value = rand()%RAND_LIM;
    for(int i=0;i<global_size;++i){
        if(!(current->next = malloc(sizeof(struct list)))){
            error(1);
            return -20022002;
        }
        current->next->prev = current;
        current->value = rand()%RAND_LIM;
        current = current->next;
    }

    // Threads:
    pthread_t thr1;
    pthread_t thr2;

    pthread_mutex_init(&mutex,NULL);

    pthread_create(&thr1,NULL,eater,field);
    pthread_create(&thr2,NULL,eater,current);

    pthread_join(thr1,NULL);
    pthread_join(thr2,NULL);

    pthread_mutex_destroy(&mutex);
#ifdef DEBUG
        printf("global_size %d",global_size);
#endif
    return 0;
}
