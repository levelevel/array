#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "array.h"

//CPU時間とメモリを表示
#include <sys/time.h>
#include <sys/resource.h>
void print_usage() {
#ifdef __linux__
    struct rusage ru;
    getrusage(RUSAGE_SELF, &ru);
    printf("User:   %ld.%03ld sec\n", ru.ru_utime.tv_sec, ru.ru_utime.tv_usec/1000);
    printf("Sys:    %ld.%03ld sec\n", ru.ru_stime.tv_sec, ru.ru_stime.tv_usec/1000);
    printf("Memory: %ld MB\n", ru.ru_maxrss/1024);
#endif
}

static char DATA1[] = "data1";
static char DATA2[] = "data2";
static char DATA3[] = "data3";

//機能テスト
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
    //assert(get_array(array, 20)==DATA2);//Eror
    free_array(array);

    //サイズ固定
    array = new_array(0);
    put_array(array, 9, NULL);
    assert(array->num==10);
    assert(array->capacity==16);
    fix_array_size(array);
    assert(array->size_fixed);
    assert(array->num==array->capacity);
    put_array(array, 9, NULL);
    //put_array(array, 10, NULL);//Error
    //pop_array(array);//Error
    //push_array(array, NULL);//Error

    //サイズ固定解除
    unfix_array_size(array);
    put_array(array, 10, NULL);
    pop_array(array);
    push_array(array, NULL);
    assert(array->num==11);
    free_array(array);

    printf("== Functional Test: OK\n");
}

//性能テスト
void test_array_speed(long size) {
    printf("== Speed Test: n=%ld\n", size);
    int psize = size/2;
    array_t *array = new_array(0);

    for (int i=0; i<size; i++) {
        put_array(array, i, NULL);
    }
    for (int i=0; i<psize; i++) {
        pop_array(array);
    }
    for (int i=0; i<psize; i++) {
        push_array(array, NULL);
    }
    assert(num_array(array)==size);

    free_array(array);

    //結果表示
    print_usage();
}

int main(int argc, char **argv) {
    printf("Start Test\n");
    test_array();
    test_array_speed(200*1000*1000);
}
