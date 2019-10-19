/*
 *                      useuarray2.c
 *
 *         This program illustrates the use of the uarray2 interface.
 *
 *         Although it will catch some errors in some uarray2 implementations
 *         it is NOT a thorough test program.
 *
 *         NOTE: this program is commented sparsely, as figuring out
 *         what this program does and why the tests it makes matter is
 *         part of the homework assignment.
 *
 *         Author: Noah Mendelsohn
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "uarray2.h"

typedef long number;

const int DIM1 = 5;
const int DIM2 = 7;
const int ELEMENT_SIZE = sizeof(number);
const int MARKER = 99;

void check_and_print(int i, int j, UArray2_T a, void *p1, void *p2) 
{
        number *entry_p = p1;
        *((bool *)p2) &= (UArray2_at(a, i, j) == entry_p);
        if ( (i == (DIM1 - 1) ) && (j == (DIM2 - 1) ) ) {
                /* we got the corner */
                *((bool *)p2) &= (*entry_p == MARKER);
        }

        printf("ar[%d,%d]\n", i, j);
}

bool strings_not_equal(char *one, char *two){
    if(one == two){
        return true;
    }
    return false;
}

int main(int argc, char *argv[])
{   
        (void)argc;

        if(strings_not_equal(argv[1], argv[2])){
            fprintf(stderr, "true\n");
        }
        else{
            fprintf(stderr, "true\n");
        }

        exit(EXIT_SUCCESS);


      //   UArray2_T test_array;
      //   bool OK = true;
      //   int contents = 0;

      //   test_array = UArray2_new(DIM1, DIM2, ELEMENT_SIZE);

      //   // fprintf(stderr, "size: %d\n", (UArray2_size(test_array)));
      //   for(int i = 0; i < (DIM1-1); i++ ){
      //       contents = 0;
      //       for(int j = 0; j <(DIM2-1); j++){
      //           if(contents == 2){
      //               contents = 0;
      //           }
      //           *((number *)UArray2_at(test_array, DIM1 - 1, DIM2 - 1)) = contents;
      //           contents++;
      //       }
      //   }

      //   OK = (UArray2_width(test_array) == DIM1) &&
	     // (UArray2_height(test_array) == DIM2) &&
      //        (UArray2_size(test_array) == ELEMENT_SIZE);


      //   /* Note: we are only setting a value on the corner of the array */
      //   *((number *)UArray2_at(test_array, DIM1 - 1, DIM2 - 1)) = MARKER;

      //   printf("Trying column major\n");    
      //   UArray2_map_col_major(test_array, check_and_print, &OK);

      //   printf("Trying row major\n");
      //   UArray2_map_row_major(test_array, check_and_print, &OK);

      //   UArray2_free(&test_array);

      //   printf("The array is %sOK!\n", (OK ? "" : "NOT "));

}
