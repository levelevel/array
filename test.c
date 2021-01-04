#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "array.h"

static char DATA1[] = "data1";
static char DATA2[] = "data2";
static char DATA3[] = "data3";

void test_array(void) {
    array_t *array, *array2;

    array = new_array(10);
    assert(array->capacity==10);
    assert(num_array(array)==0);
    free_array(array);

    array = new_array(0);
    put_array(array, 10, DATA1);
    assert(num_array(array)==11);
    assert(get_array(array, 10)==DATA1);
    put_array(array, 20, DATA2);
    assert(num_array(array)==21);
    assert(get_array(array, 20)==DATA2);
    assert(get_array(array, 0)==NULL);
    del_array(array, 10);
    assert(num_array(array)==20);
    assert(get_array(array, 10)==NULL);
    assert(get_array(array, 19)==DATA2);
    free_array(array);

    array = new_array(0);
    push_array(array, DATA1);
    assert(num_array(array)==1);
    assert(get_array(array, 0)==DATA1);
    push_array(array, DATA2);
    assert(num_array(array)==2);
    assert(get_array(array, 0)==DATA1);
    assert(get_array(array, 1)==DATA2);
    assert(pop_array(array)==DATA2);
    assert(num_array(array)==1);
    free_array(array);

    array = new_array(0);
    put_array(array, 100, DATA1);
    put_array(array, 200, DATA2);
    array2 = dup_array(array);
    assert(num_array(array2)==201);
    assert(get_array(array2, 100)==DATA1);
    assert(get_array(array2, 199)==NULL);
    assert(get_array(array2, 200)==DATA2);
    put_array(array2, 300, DATA3);
    assert(num_array(array2)==301);
    assert(get_array(array2, 300)==DATA3);
    assert(num_array(array)==201);
    free_array(array);
    free_array(array2);

    array = new_array(0);
    put_array(array, 10, DATA1);
    put_array(array, 20, DATA2);
    set_array_size(array, 50);
    assert(num_array(array)==50);
    assert(get_array(array, 49)==NULL);
    set_array_size(array, 15);
    assert(num_array(array)==15);
    assert(get_array(array, 10)==DATA1);
    //assert(get_array(array, 20)==DATA2);
    free_array(array);

#define SIZE 10000000
    array = new_array(0);
    for (int i=0; i<SIZE; i++) {
        put_array(array, i, NULL);
    }
    for (int i=0; i<SIZE/2; i++) {
        pop_array(array);
    }
    for (int i=0; i<SIZE/2; i++) {
        push_array(array, NULL);
    }
    assert(num_array(array)==SIZE);
    free_array(array);
}

int main(int argc, char **argv) {
    test_array();
}
