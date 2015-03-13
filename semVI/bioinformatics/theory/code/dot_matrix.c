#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define INCR_SIZE 100

/* Read a string of arbitrary length from the terminal */
char *read_sequence()
{
    int c, i = 0, curr_size = 100;
    char *sequence = (char *) malloc(curr_size);
    do {
        c = getchar();
        sequence[i++] = c;
        if (i > 99) {
            curr_size += INCR_SIZE;
            realloc(sequence, curr_size);
        }
    } while (c != '\n');
    sequence[--i] = '\0';

    return sequence;
}

/* Creates a dot-plot matrix of the read sequences */
char **create_dot_matrix(char *first_seq, char *second_seq, uint32_t length)
{
    char **matrix = (char **) malloc( (length + 1)* sizeof(char *));
    for(uint32_t i=0; i < length + 1; ++i) {
        matrix[i] = (char *) malloc(length + 1);
    }

    /* Initialize the first row and first column with first sequence
     * and second sequence respectively. */
    matrix[0][0] = ' ';
    for(uint32_t i = 0; i < length; ++i) matrix[0][i+1] = first_seq[i];
    for(uint32_t i = 0; i < length; ++i) matrix[i+1][0] = second_seq[i];


    for(uint32_t i = 0; i < length; ++i) {
        for(uint32_t j = 0; j < length; ++j) {
            if (first_seq[i] == second_seq[j])
                matrix[j+1][i+1] = '*';
            else
                matrix[j+1][i+1] = '-';
        }
    }

    return matrix;
}

/* Print the dot-plot matrix in a nicely aligned manner */
void print_matrix(char **matrix, uint32_t length)
{
    printf("\n");
    for(uint32_t i = 0; i < length; ++i) {
        printf("%s\n", matrix[i]);
    }
}

/* Create the global alignment from the dot-matrix */
char *alignment(char **matrix, uint32_t length)
{
    char *alignment = (char *) malloc(length);

    for(uint32_t i = 0; i < length; ++i) {
        if (matrix[i + 1][i + 1] == '*')
            alignment[i] = '|';
        else
            alignment[i] = '-';
    }

    return alignment;
}

void print_alignment(char *alignment, char *first_seq, char *second_seq)
{
    puts("\n");
    puts(first_seq);
    puts(alignment);
    puts(second_seq);
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

    if (first_len != second_len) {
        printf("Error! Please ensure that sequence length is same.");
        exit(0);
    }

    char **matrix = create_dot_matrix(first_seq, second_seq, first_len);

    print_matrix(matrix, first_len);
    print_alignment(alignment(matrix, first_len), first_seq, second_seq);

    free(matrix);
    free(first_seq);
    free(second_seq);

    return 0;
}
