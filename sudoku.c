#include <stdlib.h>
#include <pnmrdr.h>
#include <seq.h>
#include "uarray2.h"
#include <stdbool.h>
#include <assert.h>

#define T UArray2_T

// array used to check if there are duplicates
typedef struct{
  bool valid;
  int temp_a[27];
} check;

// populates a sequences with a sentinel value, in this case it's a -1
void reset_seq(Seq_T *seq, int stnl) {
  for (int i = 0; i < 9; i++) {
    Seq_put(*seq, i, &stnl);
  }
}

// checks every 3 by 3 box and determine if the numbers are valid for a 
// solve sudoku
void solved_box(int r, int c, T a, void *p1, void *p2){
  (void) a;
  check *p3 = p2;
  int value = *((int *) p1) - 1;
  if (c > 2 && c < 6){
    value = value + 9;
  }
  if(c > 5 && c < 9){
    value = value + 18;
  }

  if(p3->temp_a[value] == -1) {
    p3->temp_a[value] = (*(int *)p1);
  }
  else {
    p3->valid = false;
  }
  if(c == 8 && (r% 3)== 2){
    for (int i = 0; i < 27; i++) {
      p3->temp_a[i] = -1;   
    }
  }
}

// checks each row of the sudoku and determines there are no repeats
void solved_row(int r, int c, T a, void *p1, void *p2){
  (void) r;
  (void) a;
  (void) p1;
  check *p3 = p2;
  int value = *((int *) p1) - 1;
  if(p3->temp_a[value] == -1) {
    p3->temp_a[value] = (*(int *)p1);
  }
  else {
    p3->valid = false; 
  }
  if(c == 8){
      for (int i = 0; i < 9; i++) {
        p3->temp_a[i] = -1;   
      }
    }
} 

// determines each column of the sudoku has no repeats
void solved_col(int r, int c, T a, void *p1, void *p2){
  (void) c;
  (void) a;
  (void) p1;
  check *p3 = p2;
  int value = *((int *) p1) - 1;
  if(p3->temp_a[value] == -1) {
    p3->temp_a[value] = (*(int *)p1);
  }
  else {
    p3->valid = false;
  }
  if(r == 8){
      for (int i = 0; i < 9; i++) {
        p3->temp_a[i] = -1;
      }
    }
} 

// This function determines whether the sudoku is solved or not, return true
// is solved and returns false if it not solved
bool solved(FILE *fptr) {
  Pnmrdr_T map = Pnmrdr_new(fptr);
  Pnmrdr_mapdata data = Pnmrdr_data(map);
  assert(data.type == Pnmrdr_gray);
  bool final = true;
  if ((int)data.width != 9 && (int) data.height != 9) {
    Pnmrdr_free(&map); 
    fclose(fptr);
    exit(1);  
  }
  else {
    bool done = false;
    UArray2_T sdku = UArray2_new (data.width, data.height, sizeof(int));
    for(int i = 0; i < (int)(data.width); i++){
      for(int j = 0; j < (int)(data.height); j++){
        *((int *) UArray2_at(sdku, i, j)) = (int)Pnmrdr_get(map);
        if (*((int *) UArray2_at(sdku, i, j)) < 1 || 
            *((int *) UArray2_at(sdku, i, j)) > 9){
          done = true;
        }
      }
    }
    if (done == true) {
      UArray2_free(&sdku);
      Pnmrdr_free(&map);
      fclose(fptr);
      exit(1);
    }
    check *c = malloc(sizeof(*c));
    c->valid = true;
    for (int i = 0; i < 27; i++) {
      c->temp_a[i] = -1;
    }
    UArray2_map_col_major(sdku, solved_col, c);
    UArray2_map_row_major(sdku, solved_row, c);
    UArray2_map_row_major(sdku, solved_box, c);

    final = c->valid;
    UArray2_free(&sdku);
    free(c);
  }
  Pnmrdr_free(&map);

  return final;
}

int main(int argc, char *argv[]) {
  FILE *fptr;
  if (argc == 1) {
    fptr = stdin;
    if(solved(fptr) == true){
          exit(0);
        } 
        else{
          exit(1);
        }
  }
  else if (argc == 2) {
    fptr = fopen(argv[1], "rb");
    bool finish = solved(fptr);
    fclose(fptr);
    if(finish== true){
      exit(0);
    } 
    else{
      exit(1);
    }
  }
  else if (argc > 2){
    exit(EXIT_FAILURE);
  }
  exit(1);
}
#undef T