#include "../dynamic-array.h"
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#define RESIZE_RATE (2)

struct dynamic_array_node{
    void* value;
};

struct dynamic_array{
    struct dynamic_array_node** nodes;
    size_t size;
    size_t current_size;
    pthread_mutex_t lock;
};

struct dynamic_array_node* new_node(void* value){
    struct dynamic_array_node* new_node = (struct dynamic_array_node*)malloc(sizeof(struct dynamic_array_node));
    new_node->value = value;
    
    return new_node;
}


struct dynamic_array * dynamic_array_new(size_t initial_capacity){
    struct dynamic_array* ary = (struct dynamic_array*)malloc(sizeof(struct dynamic_array));
    struct dynamic_array_node** nodes = (struct dynamic_array_node**)malloc(initial_capacity*sizeof(struct dynamic_array_node*));
    ary->nodes = nodes;
    ary->size = initial_capacity;
    ary->current_size = 0;
    pthread_mutex_init(&(ary->lock),NULL);
    //printf("INIT %ld %ld\n", ary->size, ary->current_size);

    for(int i=0; i<initial_capacity; i++){
        nodes[i]=NULL;
    }

    return ary;
}

void dynamic_array_add(struct dynamic_array *ary, void *value){
    if(ary==NULL || value ==NULL){
        return;
    }

    pthread_mutex_lock(&(ary->lock));

    ary->nodes[ary->current_size] = new_node(value);
    ary->current_size += 1;
    //printf("ADD: %s %ld\n", (char*)value, ary->current_size);
    //resize
    if(ary->current_size == ary->size){
        size_t new_size = ary->size*RESIZE_RATE;
        ary->size = new_size;
        ary->nodes = realloc(ary->nodes,new_size*sizeof(struct dynamic_array_node*));

        //set the second half resized array as NULL
        for(int i=ary->current_size; i <new_size; i++){
            ary->nodes[i]=NULL;
        }
    }
    
    pthread_mutex_unlock(&(ary->lock));
}

void * dynamic_array_get(struct dynamic_array *ary, size_t index){
    if(ary==NULL){
        return NULL;
    }
    pthread_mutex_lock(&(ary->lock));
    void* value =  ary->nodes[index]->value;
    pthread_mutex_unlock(&(ary->lock));

    //printf("GET   : %s\n", (char*)ary->nodes[index]->value);
    return value;
}

void * dynamic_array_remove(struct dynamic_array *ary, size_t index){
    if(ary==NULL){
        return NULL;
    }

    pthread_mutex_lock(&(ary->lock));

    if(ary->nodes[index]==NULL){
        puts("here");
        pthread_mutex_unlock(&(ary->lock));
        return NULL;
    }

    //get the target value from node
    void* target_value = ary->nodes[index]->value;

    //free the node
    free(ary->nodes[index]);

    //move the rest element
    for(int i = index; i<ary->current_size-1; i++){
        ary->nodes[i]= ary->nodes[i+1];
    }

    //set the last as NULL
    size_t last_node_index = ary->current_size-1;
    ary->nodes[last_node_index]=NULL;

    //decrease the current size
    ary->current_size-=1;

    pthread_mutex_unlock(&(ary->lock));
    //user need to free it
    return target_value;
}

void dynamic_array_destroy(struct dynamic_array * ary){
    if(ary==NULL){
        return;
    }

    for(int i=0; i <ary->current_size; i++){
        free(ary->nodes[i]);
    }

    free(ary->nodes);
    pthread_mutex_destroy(&(ary->lock));
    free(ary);    
}
