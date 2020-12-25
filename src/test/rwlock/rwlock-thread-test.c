#include <stdio.h>
#include <stdlib.h>

#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include <string.h>
#include "../../src/rwlock/dynamic-array.c"

int setup(void** state){
    struct dynamic_array* ary = dynamic_array_new(10);
    assert_non_null(ary);
    *state = ary;
    return 0;
}

int teardown(void** state){
    dynamic_array_destroy(*state);
    return 0;
}

void* add1_thread_function(void* arg){
    struct dynamic_array* ary = (struct dynamic_array*)arg;

    char* strings[] = {"value0","value1","value2","value3","value4","value5","value6","value7","value8","value9"};

    for(int i=0; i<10; i++){
        char* str = malloc(10);
        //char* str;
        sprintf(str,"value%d",i);
        dynamic_array_add(ary, strings[i]);
    }
    return NULL;
}

/*
    test add is thread safe in 2 threads
*/
void thread_test_add1(void** state) {
    //get ary from setup
    struct dynamic_array* ary = *state;

    pthread_t threads[2];

    //create threads
    for (int i = 0; i < 2; i++){
        pthread_create(threads + i, NULL, add1_thread_function, ary);
    }

    //threads join
    for (int i = 0; i < 2; i++){
        pthread_join(threads[i], NULL);
    }

    int ctr[10];
    for(int i=0; i<10; i++){
        ctr[i]=0;
    }

    //assert
    for(int i=0; i<20;i++){
        char* res = (char*)dynamic_array_get(ary,i);
        for(int j=0; j<10; j++){
            char* temp = malloc(10);
            sprintf(temp,"value%d", j);
            if(strcmp(res,temp)==0){
                //printf("str : %s %s %d \n", res, temp, j);
                ctr[j]+=1;
                break;
            }
            free(temp);
        }
    }

    for(int i=0;i<10;i++){
        assert_true(ctr[i]==2);
    }

    assert_true(ary->current_size==20);
    assert_true(ary->size==40);
}


void* add_remove1_add_thread_function(void* arg){
    struct dynamic_array* ary = (struct dynamic_array*)arg;

    char* strings[] = {"value0","value1","value2","value3","value4","value5","value6","value7","value8","value9"};

    for(int i=0; i<10; i++){
        char* str = malloc(10);
        //char* str;
        sprintf(str,"value%d",i);
        dynamic_array_add(ary, strings[i]);
    }

    // for(int i=0; i<10; i++){
    //     dynamic_array_remove(ary, i);
    // }
    return NULL;
}

/*keep remove the first value 10 times*/
void* add_remove1_remove_thread_function(void* arg){
    struct dynamic_array* ary = (struct dynamic_array*)arg;

    for(int i=0; i<10; i++){
        dynamic_array_remove(ary, 0);
    }
    return NULL;
}

/*add and remove are separeted in different part of threads*/
void thread_test_add_remove1(void** state) {
    //get ary from setup
    struct dynamic_array* ary = *state;

    pthread_t threads1[2];
    pthread_t threads2[2];

    //create add threads
    for (int i = 0; i < 2; i++){
        pthread_create(threads1 + i, NULL, add_remove1_add_thread_function, ary);
    }

    //threads join
    for (int i = 0; i < 2; i++){
        pthread_join(threads1[i], NULL);
    }

    assert_true(ary->current_size==20);

    //create remove threads
    for (int i = 0; i < 2; i++){
        pthread_create(threads2 + i, NULL, add_remove1_remove_thread_function, ary);
    }

    //threads join
    for (int i = 0; i < 2; i++){
        pthread_join(threads2[i], NULL);
    }

    //assert
    assert_true(ary->current_size==0);
    assert_true(ary->size==40);
}

void* add_remove2_thread_function(void* arg){
    struct dynamic_array* ary = (struct dynamic_array*)arg;

    char* strings[] = {"value0","value1","value2","value3","value4","value5","value6","value7","value8","value9"};

    for(int i=0; i<10; i++){
        char* str = malloc(10);
        sprintf(str,"value%d",i);
        dynamic_array_add(ary, strings[i]);
    }

    for(int i=0; i<10; i++){
        dynamic_array_remove(ary, 0);
    }
    return NULL;
}

/*add and remove togethere in thread*/
void thread_test_add_remove2(void** state) {
    //get ary from setup
    struct dynamic_array* ary = *state;

    pthread_t threads1[2];
    pthread_t threads2[2];

    //create add threads
    for (int i = 0; i < 2; i++){
        pthread_create(threads1 + i, NULL, add_remove2_thread_function, ary);
    }

    //threads join
    for (int i = 0; i < 2; i++){
        pthread_join(threads1[i], NULL);
    }

    //assert
    assert_true(ary->current_size==0);
}

int main() {
    
    struct CMUnitTest tests[] = {
        cmocka_unit_test_setup_teardown(thread_test_add1,setup,teardown),
        cmocka_unit_test_setup_teardown(thread_test_add_remove1,setup,teardown),
        cmocka_unit_test_setup_teardown(thread_test_add_remove2,setup,teardown)
    };
    
    return cmocka_run_group_tests(tests, NULL, NULL);
}