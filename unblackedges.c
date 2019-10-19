#include <stdlib.h>
#include "bit2.h"
#include <stdbool.h>
#include <pnmrdr.h>
#include <seq.h>
#include <assert.h>

#define T Bit2_T

typedef struct{
    int row;
    int col;
} location;

// reads in the information from the file, and places it into a new Bit2_T
// data structure
T pbmread (FILE *inputfp){
    Pnmrdr_T map = Pnmrdr_new(inputfp);
    Pnmrdr_mapdata data = Pnmrdr_data(map);
    assert(data.type == Pnmrdr_bit); 
    if (data.width == 0 || data.height == 0) {
        fprintf(stderr, "Not valid bitmap\n");
        Pnmrdr_free(&map);
        fclose(inputfp);
        exit(EXIT_FAILURE); 
    }
    T bit_map = Bit2_new(data.width, data.height);
    for(int i = 0; i < (int)(data.height); i++){
        for(int j = 0; j < (int)(data.width); j++){
          Bit2_put( bit_map, i, j, (int)Pnmrdr_get(map));
        }
    }
    Pnmrdr_free(&map);
    return bit_map;
}

// takes in the location, row index and column index and flips the value into
// black or 1
void invert(int r, int c, T a, int bit_val){
    if(bit_val == 1){
        Bit2_put(a, r, c, 0);
    }
}

// based on the row and column index from the location object, it determines
// if the neighbors can possibly be a blackedge
bool check_n(Seq_T *recur, T bit_map, location *curr){
    bool change = false;
    if(curr->col > 0 && Bit2_get(bit_map, curr->row, curr->col-1)==1){
        location *temp = malloc(sizeof(temp));
        temp->row = curr->row;
        temp->col = curr->col -1;
        Seq_addhi(*recur, temp);
        change = true;
    }
    if(curr->col < Bit2_width(bit_map)-1 && Bit2_get(bit_map, curr->row, 
                curr->col+1)==1){
        location *temp = malloc(sizeof(temp));
        temp->row = curr->row;
        temp->col = curr->col +1;
        Seq_addhi(*recur, temp);
        change = true;
    }
    if(curr->row > 0 && Bit2_get(bit_map, curr->row-1, curr->col)==1){
        location *temp = malloc(sizeof(temp));
        temp->col = curr->col;
        temp->row = curr->row - 1; 
        Seq_addhi(*recur, temp);
        change = true;
    }
    if(curr->row < Bit2_height(bit_map)-1 && 
                Bit2_get(bit_map, curr->row + 1, curr->col)==1){
        location *temp = malloc(sizeof(temp));
        temp->col = curr->col;
        temp->row = curr->row +1;
        Seq_addhi(*recur, temp);
        change = true;
    } 
    return change;
}

// looks at the edge of the Bit2_T object and determines if there are any
// possible black edge and adds it onto our Sequence_T
void edgesadd(T bit_map, Seq_T *recur){
    for(int r = 0; r < Bit2_height(bit_map); r++){
        if(Bit2_get(bit_map, r, 0) == 1 ){
            location *temp = malloc(sizeof(temp));
            temp->row = r;
            temp->col = 0;
            Seq_addhi(*recur, temp);
        }
        if (Bit2_get(bit_map, r, (Bit2_width(bit_map)-1)) == 1) {
            location *temp = malloc(sizeof(temp));
            temp->row = r;
            temp->col = (Bit2_width(bit_map)-1);
            Seq_addhi(*recur, temp);
        }
    }
    for(int c = 0; c < Bit2_width(bit_map); c++){
        if (Bit2_get(bit_map,0, c) == 1) {
            location *temp = malloc(sizeof(temp));
            temp->row = 0;
            temp->col = c;
            Seq_addhi(*recur, temp);
        }
        if (Bit2_get(bit_map, (Bit2_height(bit_map)-1), c) == 1) {
            location *temp = malloc(sizeof(temp));
            temp->row = (Bit2_height(bit_map)-1);
            temp->col = c;
            Seq_addhi(*recur, temp);
        }
    }
}

// to check for black edges, the program checks it similar to how a graph
// traversal works, breadth-first search (BFS)
void check_black(T bit_map){
    location *curr; 
    bool end;
    Seq_T recur = Seq_new(20);
    Seq_T neighbors = Seq_new(20);
    edgesadd(bit_map, &recur);

    while(Seq_length(recur) != 0){
        curr = (location *) Seq_remlo(recur);
        invert(curr->row, curr->col, bit_map,
                    Bit2_get(bit_map, curr->row, curr->col));
        end = check_n(&neighbors, bit_map, curr);
        free(curr);
        if(end == true){
            while(Seq_length(neighbors) != 0){
                curr = (location *) Seq_remlo(neighbors);
                invert(curr->row, curr->col, bit_map, 
                            Bit2_get(bit_map, curr->row, curr->col) );
                end = check_n(&recur, bit_map, curr);
                free(curr);
            }
        }
    }
    Seq_free(&recur);
    Seq_free(&neighbors);
}

// prints out the Bit2_T information into the file pointer, map function
void writeBM(int r, int c, T a, int bit_val, void *p1){
    (void) r;
    fprintf(p1, "%d", bit_val);
    if(c == Bit2_width(a)-1 || c % 70 == 69){
        fprintf(p1, "\n");
    }
}

// prints out the Bit2_T information into the file pointer
void pbmwrite(FILE *outputfp, T bit_map){
    fprintf(outputfp, "P1\n" );
    fprintf(outputfp, "%d %d\n",Bit2_width(bit_map), Bit2_height(bit_map) );
    Bit2_map_row_major(bit_map, writeBM, outputfp);
}

int main(int argc, char *argv[]) {
    FILE *fptr;
    FILE *outputfp;
    T bit_map;
    if (argc == 1) {
        fptr = stdin;
        outputfp = stdout;
        bit_map = pbmread(fptr);
        check_black(bit_map);
        pbmwrite(outputfp,bit_map);
        Bit2_free(&bit_map);
    }
    else if (argc == 2) {
        fptr = fopen(argv[1], "rb");
        outputfp = stdout;
        bit_map = pbmread(fptr);
        check_black(bit_map);
        pbmwrite(outputfp,bit_map);
        Bit2_free(&bit_map);
        fclose(fptr);
    }
    else if (argc > 2){
        fprintf(stderr, "Too many arguments.\n" ); 
    }

    return EXIT_SUCCESS;
}
#undef T