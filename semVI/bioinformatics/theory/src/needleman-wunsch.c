#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>
#include "helpers.h"

/* Constants */
const int GAP_PENALTY = -1;
const int MATCH_SCORE = 1;
const int MISMM_SCORE = -3;

/* Initializes the first row and first column of the matrix */
int **initialize_matrix(int column, int row)
{
    int **matrix = (int **) calloc((row + 1), sizeof(int *));
    for(uint32_t i=0; i < row + 1; ++i) {
        matrix[i] = (int *) calloc(column + 1, sizeof(int));
    }

    matrix[0][0] = 0;
    for(uint32_t i = 0; i < column; ++i)
        matrix[0][i+1] = matrix[0][i] + GAP_PENALTY;
    for(uint32_t i = 0; i < row; ++i)
        matrix[i+1][0] = matrix[i][0] + GAP_PENALTY;

    return matrix;
}

/* Populates the cells of matrix using the Needleman-Wunsch algorithm
 * and values from the constants section.
 */
void solve_matrix(int **matrix, char *first_seq, char *second_seq,
                    int first_len, int second_len)
{
    int diag_score;
    for(uint32_t i = 1; i <= second_len; ++i) {
        for(uint32_t j = 1; j <= first_len; ++j) {
            diag_score = (first_seq[j-1] == second_seq[i-1] ? MATCH_SCORE :
                          MISMM_SCORE);
            matrix[i][j] = MAX(MAX(matrix[i-1][j-1] + diag_score,
                                   matrix[i-1][j] + GAP_PENALTY),
                               matrix[i][j-1] + GAP_PENALTY);
        }
    }
}

bool assert_valid(int i, int j) {
    puts("here");
    return (i >= 0 && j >= 0);
}

/* Pretty prints the alignment using the solved matrix */
void print_alignment(int **matrix, char *first_seq, char *second_seq)
{
    int i = strlen(second_seq);
    int j = strlen(first_seq);
    int k = 0, max;
    char *f_align = (char *) malloc(i+j);
    char *s_align = (char *) malloc(i+j);
    char *midline = (char *) malloc(i+j);

    /* Properly terminate the string */
    do {
        max = MAX(MAX(matrix[i-1 >= 0 ? i-1 : 0][j-1 >= 0 ? j-1 : 0],
                      matrix[i-1 >= 0 ? i-1 : 0][j]),
                  matrix[i][j-1 >= 0 ? j-1 : 0]);

        if (i-1 >= 0 && matrix[i-1][j] == max) {
            --i;
            f_align[k] = '-';
            s_align[k] = second_seq[i];
            midline[k] = ' ';
        } else if ( j-1 >= 0 && matrix[i][j-1] == max) {
            --j;
            f_align[k] = first_seq[j];
            s_align[k] = '-';
            midline[k] = ' ';
        } else if ( i-1 >=0 && j-1 >= 0 && matrix[i-1][j-1] == max) {
            --i;
            --j;
            midline[k] = first_seq[j] == second_seq[i] ? '|' : ' ';
            f_align[k] = first_seq[j];
            s_align[k] = second_seq[i];
        }

        ++k;

    } while (i != 0 || j != 0);

    f_align[k] = '\0';
    midline[k] = '\0';
    s_align[k] = '\0';

    /* Strings are read in reverse direction. So revert them back before
     * printing */
    f_align = strrev(f_align);
    s_align = strrev(s_align);
    midline = strrev(midline);

    puts(f_align);
    printf("%s\n", midline);
    puts(s_align);
}

void print_matrix(int **matrix, int column, int row)
{
    for(int i = 0; i <= row; ++i) {
        for (int j = 0; j <= column; ++j) {
            printf("%4d ", matrix[i][j]);
        }
        puts("\n");
    }
}

int main(int argc, char *argv[])
{
    char *first_seq, *second_seq;
    uint32_t first_len, second_len;

    printf("Enter a sequence?\n");
    first_seq = read_sequence();
    first_len = strlen(first_seq);

    printf("Enter another sequence?\n");
    second_seq = read_sequence();
    second_len = strlen(second_seq);

    if (first_len == 0 || second_len == 0) {
        printf("Invalid input.");
        exit(0);
    }

    int **matrix = initialize_matrix(first_len, second_len);

    solve_matrix(matrix, first_seq, second_seq, first_len, second_len);

    print_matrix(matrix, first_len, second_len);

    print_alignment(matrix, first_seq, second_seq);

    free(matrix);
    free(first_seq);
    free(second_seq);

    return 0;
}
