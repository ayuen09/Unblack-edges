#include <stdlib.h>
#include <ctype.h>
#include "uarray.h"
#include <stdbool.h>

#ifndef UARRAY2_H_
#define UARRAY2_H_
#define T UArray2_T
typedef struct T *T;
//the struct that defines UArray2


/*Function: UArray2_at
Gets the element at that (row, col) in the 
    UArrary2_T object called array
Returns a void *, which then the user converts it 
    back to the appropriate object type that exists within the array*/
void *UArray2_at(T a, int i, int j);

/*Function: UArray2_new
Allocates memory for the array given the size of the information, 
    and returns a pointer to the UArray2_T with the inputted width and height
Since this returns pointer to a UArray2_T we’re assuming that the user is 
    using this function to allocate memory for their 
    unboxed 2d array (UArray2_T)*/
T UArray2_new(int width, int height, int ELEMENT_SIZE);

/*Function: UArray2_width
Returns the width of the UArray2_T named test_array
Input must be UArray2_T object and the return type is an integer*/
int UArray2_width(T test_array);

/*Function: UArray2_height
Returns the height of test_array
Input must be UArray2_T object and the return type is an integer*/
int UArray2_height(T test_array);

/*Function: UArray2_map_col_major
A map function that prints out the 2-D data struct column wise
Input must include a UArray2_T, a function that will print a UArray2_T 
    column-wise, and a boolean type
Boolean will be updated to false if a certain location in the array 
    does not match accordingly*/
void UArray2_map_col_major( T test_array, 
    void apply(int i, int j, T a,
     void *p1, void *p2), void *OK);

/*Function; UArray2_map_row_major
A map function that prints out the 2-D data struct row wise
Input must include a UArray2_T, a function that will print a UArray2_T 
    across rows, and a boolean type
Boolean will be updated to false if a certain location in the array 
    does not match accordingly*/
void UArray2_map_row_major( T test_array, 
    void apply(int i, int j, T a, 
        void *p1, void *p2), void *OK);

/*Function: UArray2_free
Deallocates memory and free memory in test_array and frees the
     test_array object
Input is an UArray2_T object (shouldn’t be a pointer as it would 
    make the implementation a double pointer)*/
void UArray2_free(T *test_array);

/*Function: UArray2_size
Returns the number of elements that occupies within the UArray2_T object 
    named test_array
Input must be a UArray2_T object that is allocated, cannot be a NULL pointer*/
int UArray2_size(T test_array);

#undef T
#endif