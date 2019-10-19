#include "bit2.h"
#include <assert.h>
#define T Bit2_T

struct T{
        int width;
        int height;
        Bit_T bitArray;
};

int Bit2_get(T a, int row, int col) {
        int index = a->width*(row)+col;
        int value = Bit_get(a->bitArray, index);
        return value;
}

int Bit2_put(Bit2_T a, int row, int col, int bit_val) {
        int index = a->width*(row)+col;
        int returnInt = Bit_put(a->bitArray, index, bit_val);
        return returnInt;
}

T Bit2_new(int width, int height) {
        int length = width * height;
        Bit2_T new = malloc(sizeof(*new));
        assert(new != NULL);
        new->bitArray = Bit_new(length);
        new->width = width;
        new->height = height;
        return new;
}

int Bit2_width(T test_array) {
        return test_array->width;
}

int Bit2_height(T test_array) {
        return test_array->height;
}

void Bit2_map_col_major(T test_array, void apply(int r, int c, Bit2_T a,
    int bit_val, void *p1), void *OK) {
        int row = 0;
        int col = 0;
        for(int i = 0; i < (test_array->width* test_array->height); i++){
                row = i % test_array->height;
                col = i / test_array->height;
                apply(row, col, test_array, Bit2_get(test_array, row, col), OK);
        }
}

void Bit2_map_row_major(T test_array, 
        void apply(int r, int c, Bit2_T a, int bit_val,
                void *p1), void *OK) {
        int row = 0;
        int col = 0;
        for(int i = 0; i < (test_array->width* test_array->height); i++){
                col = i % test_array->width;
                row = i / test_array->width;
                apply(row, col, test_array, Bit2_get(test_array, row, col), OK);
        }
}

void Bit2_free(T *a) {
        Bit_T temp = (*a)->bitArray;
        Bit_free(&temp);
        free(*a);
}
#undef T