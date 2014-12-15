#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
for each superblock, we will store size of superblock (close to a page), and indices of source/destination that they will hit

Then, for each superblock, we will have to iterate through the blocks and perform the block-vector computation
*/

void smvm_2x2( int bm, const int *b_row_start, const int *b_col_idx, const double *b_value, const double *x, double *y)
{
        int i, jj;
        for (i =0; i<bm; i++, y+=2){
                register double d0 = y[0];
                register double d1 = y[1];
                for (jj = b_row_start[i]; jj<b_row_start[i+1];
                         jj++, b_col_idx++, b_value += 2*2) {
                        d0 += b_value[0] * x[b_col_idx[0]+0];
                        d1 += b_value[2] * x[b_col_idx[0]+0];
                        d0 += b_value[1] * x[b_col_idx[0]+1];
                        d1 += b_value[3] * x[b_col_idx[0]+1];
                }
                y[0]=d0;
                y[1]=d1;
        }
}

int main(int argc, char *argv[])
{
        clock_t start;
        clock_t end;
        double read_time;
        double compute_time;

        start = clock();

        // READ THE MATRIX 
        FILE *matrix_in;
        matrix_in = fopen(argv[1], "r");
        if (matrix_in == NULL)
        {
                printf("Could not open matrix file");
                exit(1);
        }
        int num_rows, num_cols; 
        int num_sblocks;
        int **superblocks;
        
        // read in the number of superblocks
        fscanf(matrix_in, "%d %d %d ", &num_rows, &num_cols, &num_sblocks);
        // allocate space for num_sblocks int pointers (int pointer is the 'same' as int array)
        superblocks = malloc(sizeof(int *)*num_sblocks);
        
        // will be reused 
        int sblock_i, block_i;
        int num_blocks, sblock_size;
        int block_id, block_size;
        int* cur_sblock;
        for (sblock_i = 0; sblock_i < num_sblocks; sblock_i++)
        {
                // read in the current superblock size and the number of blocks
                fscanf(matrix_in, "%d %d ", &sblock_size, &num_blocks);
                superblocks[sblock_i] = malloc(sizeof(int)*(sblock_size + 1));
                cur_sblock = superblocks[sblock_i];

                cur_sblock[0] = num_blocks;
                cur_sblock += 1;
                for (block_i=0; block_i < num_blocks; block_i++)
                {
                        // read the block id into the current sblock array
                        fscanf(matrix_in, "%d ", cur_sblock);
                        switch(cur_sblock[0])
                        {
                                case 1:
                                        // 1x1 matrix
                                        fscanf(matrix_in, "%d %d %d ", &cur_sblock[1], &cur_sblock[2], &cur_sblock[3]);

                                        cur_sblock += 4;
                                        break;
                                case 2:
                                        // 2x2 matrix
                                        fscanf(matrix_in, "%d %d %d %d %d %d ",
                                                                &cur_sblock[1], &cur_sblock[2], 
                                                                &cur_sblock[3], &cur_sblock[4],
                                                                &cur_sblock[5], &cur_sblock[6]);
                                                              
                                        /**
                                        printf("R: %d C: %d Vals: %d %d %d %d\n", 
                                                                cur_sblock[1], cur_sblock[2], 
                                                                cur_sblock[3], cur_sblock[4],
                                                                cur_sblock[5], cur_sblock[6]);
                                                                */
                                        
                                        cur_sblock += 7; 
                                        break;
                                case 3:
                                        // 3x3 matrix
                                        fscanf(matrix_in, "%d %d %d %d %d %d %d %d %d %d %d ",
                                                                &cur_sblock[1], &cur_sblock[2], 
                                                                &cur_sblock[3], &cur_sblock[4],
                                                                &cur_sblock[5], &cur_sblock[6],
                                                                &cur_sblock[7], &cur_sblock[8],
                                                                &cur_sblock[9], &cur_sblock[10],
                                                                &cur_sblock[11]);
                                        
                                        /**
                                        printf("R: %d C: %d Vals: %d %d %d %d %d %d %d %d %d\n", 
                                                                cur_sblock[1], cur_sblock[2], 
                                                                cur_sblock[3], cur_sblock[4],
                                                                cur_sblock[5], cur_sblock[6],
                                                                cur_sblock[7], cur_sblock[8],
                                                                cur_sblock[9], cur_sblock[10],
                                                                cur_sblock[11]); 
                                                                */
                                        
                                        cur_sblock += 12; 
                                        break;
                                case 4:
                                        // 4x4 matrix
                                        fscanf(matrix_in, "%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d ", 
                                                                &cur_sblock[1], &cur_sblock[2], 
                                                                &cur_sblock[3], &cur_sblock[4],
                                                                &cur_sblock[5], &cur_sblock[6],
                                                                &cur_sblock[7], &cur_sblock[8],
                                                                &cur_sblock[9], &cur_sblock[10],
                                                                &cur_sblock[11], &cur_sblock[12],
                                                                &cur_sblock[13], &cur_sblock[14],
                                                                &cur_sblock[15], &cur_sblock[16],
                                                                &cur_sblock[17], &cur_sblock[18]);
                                        
                                        /*
                                        printf("R: %d C: %d Vals: %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d \n", 
                                                                cur_sblock[1], cur_sblock[2], 
                                                                cur_sblock[3], cur_sblock[4],
                                                                cur_sblock[5], cur_sblock[6],
                                                                cur_sblock[7], cur_sblock[8],
                                                                cur_sblock[9], cur_sblock[10],
                                                                cur_sblock[11], cur_sblock[12],
                                                                cur_sblock[13], cur_sblock[14],
                                                                cur_sblock[15], cur_sblock[16],
                                                                cur_sblock[17], cur_sblock[18]);
                                                                */
                                        
                                        cur_sblock += 19; 
                                        break;
                                default:
                                        exit(1);
                        
                        }                        
                        
                }
        }
        fclose(matrix_in);

        end = clock();

        /* Get time in milliseconds */
        read_time = (double)(end - start) / (CLOCKS_PER_SEC / 1000.0);

        /*
        READ THE SOURCE VECTOR
        */

        FILE *src_vec_in;
        src_vec_in = fopen(argv[2], "r");
        if (src_vec_in == NULL)
        {
                printf("Could not open src vector file");
                exit(1);
        }
        int x_len;
        fscanf(src_vec_in, "%d ", &x_len);
        if (x_len != num_cols)
        {
                printf("Matrix and vector have incompatible dims\n");
                exit(1);
        }
        int* x = malloc(sizeof(int) * x_len);

        if (x == NULL)
        {
                printf("Could not malloc x");
                exit(1);
        }
        int i;
        for(i = 0; i < x_len; i++)
        {            
                fscanf(src_vec_in, "%d ", &x[i]);                
        }
        
        // allocate the destination vector
        int* y = malloc(sizeof(int) * num_rows);       

        for(i=0; i < num_rows; i++)
        {
                y[i] = 0;
        }

        if (y == NULL)
        {
                printf("Could not malloc y");
                exit(1);
        }
        

        /*
        Do the multiplication
        */
        // iterate through the superblocks in outer loop

        start = clock();
        int r, c;
        for (sblock_i = 0; sblock_i < num_sblocks; sblock_i++)
        {
                //get current superblock
                cur_sblock = superblocks[sblock_i];
                num_blocks = cur_sblock[0];

                // move the pointer up by 1
                cur_sblock += 1;
                for(block_i = 0; block_i < num_blocks; block_i++)
                {
                        // cur_sblock[1] -> row
                        // cur_sblock[2] -> col
                        r = cur_sblock[1];
                        c = cur_sblock[2]; 
                        

                        // cur_sblock[0] -> block_id of current block 
                        switch(cur_sblock[0])
                        {                                

                                case 1:
                                        // 1x1 block
                                        y[r] += cur_sblock[3] * x[c];
                                        // move to next block
                                        cur_sblock += 4;
                                        break;
                                case 2:
                                        // 2x2 block                                    
                                        y[r]   += cur_sblock[3] * x[c];
                                        y[r]   += cur_sblock[4] * x[c+1];

                                        y[r+1] += cur_sblock[5] * x[c];                                                                         
                                        y[r+1] += cur_sblock[6] * x[c+1];
                                        
                                        // move to next block
                                        cur_sblock += 7;
                                        break;
                                case 3:
                                        // 3x3 block
                                        y[r]   += cur_sblock[3] * x[c]; 
                                        y[r]   += cur_sblock[4] * x[c+1];
                                        y[r]   += cur_sblock[5] * x[c+2];
                                        
                                        y[r+1] += cur_sblock[6] * x[c]; 
                                        y[r+1] += cur_sblock[7] * x[c+1]; 
                                        y[r+1] += cur_sblock[8] * x[c+2]; 

                                        y[r+2] += cur_sblock[9] * x[c]; 
                                        y[r+2] += cur_sblock[10] * x[c+1]; 
                                        y[r+2] += cur_sblock[11] * x[c+2]; 

                                        // move to next block
                                        cur_sblock += 12;
                                        break;
                                case 4: 
                                        // 4 x 4 block
                                        y[r]   += cur_sblock[3] * x[c];
                                        y[r]   += cur_sblock[4] * x[c+1];
                                        y[r]   += cur_sblock[5] * x[c+2];
                                        y[r]   += cur_sblock[6] * x[c+3];

                                        y[r+1] += cur_sblock[7] * x[c];
                                        y[r+1] += cur_sblock[8] * x[c+1];
                                        y[r+1] += cur_sblock[9] * x[c+2];
                                        y[r+1] += cur_sblock[10] * x[c+3];

                                        y[r+2] += cur_sblock[11] * x[c];
                                        y[r+2] += cur_sblock[12] * x[c+1];
                                        y[r+2] += cur_sblock[13] * x[c+2];
                                        y[r+2] += cur_sblock[14] * x[c+3];

                                        y[r+3] += cur_sblock[15] * x[c];
                                        y[r+3] += cur_sblock[16] * x[c+1];
                                        y[r+3] += cur_sblock[17] * x[c+2];
                                        y[r+3] += cur_sblock[18] * x[c+3];
                                        
                                        // move to next block
                                        cur_sblock += 19;
                                        break;
                                default:
                                        printf("Unsupported block id %d", cur_sblock[0]);
                                        exit(1);
                        }
                }
        }   

        end = clock();

        /* Get time in milliseconds */
        compute_time = (double)(end - start) / (CLOCKS_PER_SEC / 1000.0);     

        FILE *result_writer;
        result_writer = fopen(argv[3], "w");

        // print out the result 
        for (i=0; i<num_rows; i++)
        {
                //printf("%d ", y[i]);
                fprintf(result_writer, "%d ", y[i]);
        }

        fclose(result_writer);

        //writes time results
        FILE *time_writer;
        time_writer = fopen("c_time_results.txt", "a");

        fprintf(time_writer, "%s %f %f\n", argv[1], read_time, compute_time);        

        fclose(time_writer);

        return 0; 
}