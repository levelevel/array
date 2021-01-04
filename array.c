#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "array.h"

#define ARRAY_INIT_SIZE     16
#define ARRAY_GROW_FACTOR   2

array_t *new_array(int size) {
    assert(size>=0);
    array_t *array = calloc(1, sizeof(array_t));
    array->capacity = size?size:ARRAY_INIT_SIZE;
    array->buckets = calloc(array->capacity, sizeof(void*));
    return array;
}

void free_array(array_t *array) {
    if (array) free(array->buckets);
    free(array);
}

int num_array(array_t *array) {
    assert(array);
    return array->num;
}

void put_array(array_t *array, int idx, void *data) {
    assert(array);
    assert(idx>=0);
    int new_size = array->capacity;
    while (idx>=new_size) new_size *= ARRAY_GROW_FACTOR;
    if (new_size>array->capacity) {
        array->buckets = realloc(array->buckets, new_size*sizeof(void*));
        memset(array->buckets+array->capacity, 0x00, (new_size-array->capacity)*sizeof(void*));
        array->capacity = new_size;
    }
    array->buckets[idx] = data;
    array->num++;
}

void *get_array(array_t *array, int idx) {
    assert(array);
    assert(idx>=0);
    assert(idx<array->num);
    return (array->buckets[idx]);
}

void del_array(array_t *array, int idx) {
    assert(array);
    assert(idx>=0);
    assert(idx<array->num);
    memcpy(array->buckets+idx, array->buckets+idx+1, array->num-idx-1);
    array->buckets[array->num-1] = NULL;
    array->num--;
}

void push_array(array_t *array, void *data) {
    assert(array);
    put_array(array, array->num, data);
}

void *pop_array(array_t *array) {
    assert(array);
    assert(array->num>0);
    void *data = array->buckets[--array->num];
    array->buckets[array->num] = NULL;
    return data;
}

array_t *dup_array(array_t *array) {
    assert(array);
    array_t *new = new_array(array->num);
    new->num = array->num;
    memcpy(new->buckets, array->buckets, array->num*sizeof(void*));
    return new;
}