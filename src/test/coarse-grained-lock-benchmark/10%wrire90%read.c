#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include "../../src/coarse-grained-lock/dynamic-array.c"

//vary
#define WRITE_RATIO (0.1)
#define READ_RATIO (1-WRITE_RATIO)

//fixed
#define THREAD_NUM (10)
#define INITIAL_CAPACITY (50)
#define ITERATIONS (5000)
#define WRITE_THREAD_NUM (THREAD_NUM*WRITE_RATIO)
#define READ_THREAD_NUM (THREAD_NUM*READ_RATIO)


void* read_thread_function(void* arg){
    struct dynamic_array* ary = (struct dynamic_array*)arg;

    for(int i=0; i<ITERATIONS; i++){
        dynamic_array_get(ary, i);
    }

    return NULL;
}

void* write_thread_function(void* arg){
    struct dynamic_array* ary = (struct dynamic_array*)arg;

    for(int i=0; i<ITERATIONS; i++){
        char* dummy_data = "dummy data in thread";
        dynamic_array_add(ary, dummy_data);
    }

    for(int i=0; i<ITERATIONS; i++){
        dynamic_array_remove(ary, 0);   //always remove the first one(the rest will be moved forward)
    }
    return NULL;
}

int main(){

    //create dynamic array;
    struct dynamic_array* ary = dynamic_array_new(INITIAL_CAPACITY);

    //FROM SPEC: giving your data structure a set num-ber of elements at the beginning
    for(int i=0;i<ITERATIONS;i++){
        char* dummy_data = "dummy data begining";
        dynamic_array_add(ary, dummy_data);
    }

    //pthread id
    pthread_t threads[THREAD_NUM];
    //create READ threads
    for (int i = 0; i < (int)READ_THREAD_NUM; i++){
        pthread_create(threads + i, NULL, read_thread_function, ary);
    }

    //create WRITE threads
    for (int i = 0; i < (int)WRITE_THREAD_NUM; i++){
        pthread_create(threads + (int)READ_THREAD_NUM + i, NULL, write_thread_function, ary);
    }

    //threads join
    for (int i = 0; i < THREAD_NUM; i++){
        pthread_join(threads[i], NULL);
    }

    //clean
    dynamic_array_destroy(ary);
    return 0;
}