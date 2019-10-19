#include <stdlib.h>
#include <ctype.h>
#include <bit.h>

#ifndef BIT2_H_
#define BIT2_H_
#define T Bit2_T

typedef struct T *T;


/*
Function: Bit2_get
Returns a pointer object/element at (i, j) in Bit2_T object named array 
Input must be Bit2_T object, an integer for row index, and an integer for 
        column index
Returns a pointer to the object, since function should work ideally for 
        abstract data types (int, char, long, types, …) 
*/
int Bit2_get(T a, int i, int j);

/*
Function: Bit2_put
Places a the bit value from bit_val(0, 1) at the given row index and the 
        column index in our Bit2_T object named test_array
Input must be a Bit2_T object that has already allocated memory 
        (cannot be NULL), other three parameters must be an integer type
Returns nothing
*/
int Bit2_put(T test_array, int row, int col, int bit_val);

/*
Function: Bit2_new
Creates and returns new Bit2_T array with given width and height dimensions
         given by the parameter
Parameters must be an integer type and function returns Bit2_T object
*/
T Bit2_new(int DIM1, int DIM2);


/*Function: Bit2_width
Returns the width of Bit2_T  object named test_array
Input must be a Bit2_T object and returns an integer type
*/
int Bit2_width(T test_array);

/*
Function: Bit2_height
Returns the height of Bit2_T  object named test_array
Input must be a Bit2_T object and returns an integer type
*/
int Bit2_height(T test_array);

/*
Function: Bit2_map_col_major
A map function that prints out the Bit2_T data structure across each columns 
Input must include a Bit2_T, a function that will print a Bit2_T across rows,
         and a boolean type
Boolean will be updated to false if the corner of the bit array is not a 
        black pixel
*/
void Bit2_map_col_major( T test_array, 
        void apply(int i, int j, Bit2_T a, int b_v,
         void *p1), void *OK);

/*
Function: Bit2_map_row_major
A map function that prints out the Bit2_T data structure across each rows 
Input must include a Bit2_T, a function that will print a Bit2_T across 
        columns, and a boolean type
Boolean will be updated to false if the corner of the bit array is not a 
        black pixel
*/
void Bit2_map_row_major( T test_array, 
        void apply(int i, int j, Bit2_T a, int bv,
                void *p1), void *OK);

/*
Function: Bit2_free
Deallocates memory and free memory in test_array and then frees the 
        test_array object
Input is an Bit2_T object (shouldn’t be a pointer as it would make the 
        implementation a double pointer)
*/
void Bit2_free(T *test_array);


#undef T
#endif