#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "uarray2.h"
#include <assert.h>

#define T UArray2_T

struct T{
    int width;
    int height;
    int ELEMENT_SIZE;
    UArray_T array;

};

T UArray2_new(int width, int height, int ELEMENT_SIZE){
    T temp = malloc(sizeof(struct T));
    assert(temp != NULL);
    temp->width = width;
    temp->height = height;
    temp->ELEMENT_SIZE = ELEMENT_SIZE;
    temp->array = UArray_new((width*height), ELEMENT_SIZE);
    return (temp);
}

void *UArray2_at(T a, int row, int col){
    int index = a->width*(row)+col;
    void *value = UArray_at(a->array, index);
    return value;
}

int UArray2_width(T test_array){
    return test_array->width;
}

int UArray2_height(T test_array){
    return test_array->height;
}

void UArray2_map_col_major(T test_array, void apply(int r, int c, T a, 
    void *p1, void *p2), void *OK){
    int row = 0;
    int col = 0;
    for(int i = 0; i < (test_array->width* test_array->height); i++){
        row = i % test_array->height;
        col = i / test_array->height;
        apply(row, col, test_array, UArray2_at(test_array, row, col), OK);
    }
}

void UArray2_map_row_major(T test_array, void apply(int r, int c, T a, 
        void *p1, void *p2), void *OK){
    int row = 0;
    int col = 0;
    for(int i = 0; i < (test_array->width* test_array->height); i++){
        col = i % test_array->width;
        row = i / test_array->width;
        apply(row, col, test_array, UArray2_at(test_array, row, col), OK);
    }

}

void UArray2_free(T *a){
    UArray_T temp = (*a)->array;
    UArray_free(&temp);
    free(*a);
}

int UArray2_size(T test_array){
    return (test_array->ELEMENT_SIZE);
}

#undef T