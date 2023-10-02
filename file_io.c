#include "common.h"
#define IN_FILE_SIZE 100 

int main(int argc, char** argv) {
    /* check correct usage */
    if(argc != 3)
    {
        printf("usage: %s <in_file> <out_file>\n", argv[0]);
        return 1;
    }

    /* create file with pairs of ints */
    FILE *f_int_pairs = fopen(argv[1], "w");
    if(f_int_pairs == NULL) return 1;
    for(int i = 0; i < IN_FILE_SIZE; i++)
    {
        /* write random pairs of ints*/
        fprintf(f_int_pairs, "%d, %d\n", rand_int(0, 10), rand_int(0, 10));
    }
    fclose(f_int_pairs);

    /* open in_file for reading */
    FILE *f_in = fopen(argv[1], "r");
    if(f_in == NULL) return 1; /* check correctly opened */

    /* open out_file for writing */
    FILE *f_out = fopen(argv[2], "w");
    if(f_out == NULL) return 1; /* check correctly opened */

    /* read in_file, perform calculations and output to out_file */
    int i1, i2;
    while(fscanf(f_in, "%d, %d\n", &i1, &i2) == 2) /* read from f_in until we do not read 2 values. Can instead check for EOF */
    {
        fprintf(f_out, "%d * %d = %d\n", i1, i2, i1*i2); /* write to f_out the multiplication of the 2 read in values */
    }

    /* close the files */
    fclose(f_in);
    fclose(f_out);

    return 0;
}