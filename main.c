#include <stdio.h>
#include <string.h>
#include <errno.h>

#include "eater.h"
#include "debug.c"

#define DEFAULT_SIZE 100000
#define NDEBUG

pthread_mutex_t eaters_mutex;


int size_init(char* digit){
    int size = atoi(digit);
    if(!size) {
        strerror(EINVAL);
        return 0;
    }
    return size;
}


int main(int argc, char* argv[]) {
    int size = DEFAULT_SIZE;
    if(argc>1) size = size_init(argv[1]);

    srand(time(NULL));

    struct Node* start = list_init(size);
    struct Node* end = find_end(start);

#ifdef DEBUG
    start_end_check(start,end);
    check_size(start);
#endif

    if(errno) return 0;

    // Threads:
    pthread_t thr1;
    pthread_t thr2;

    pthread_mutex_init(&eaters_mutex,NULL);

    pthread_create(&thr1,NULL,eater,start);
    pthread_create(&thr2,NULL,eater,end);

    pthread_join(thr1,NULL);
    pthread_join(thr2,NULL);

    pthread_mutex_destroy(&eaters_mutex);

    return 0;
}
