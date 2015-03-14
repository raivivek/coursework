#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>

#define INCR_SIZE 100
#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

/* Read a string of arbitrary length from the terminal.
 * NOTE: The function doesn't check whether input characters are valid
 * nucleotide or amino acids or not.
 */
char *read_sequence()
{
    int c, i = 0, curr_size = 100;
    char *sequence = (char *) malloc(curr_size);
    do {
        c = toupper(getchar());
        sequence[i++] = c;
        if (i > 99) {
            curr_size += INCR_SIZE;
            realloc(sequence, curr_size);
        }
    } while (c != '\n');
    sequence[--i] = '\0';

    return sequence;
}

/* Print an arbitrary sequence */
void print_sequence(char *sequence)
{
    printf("%s\n", sequence);
}

/* Reverse a string */
char *strrev(char *str)
{
      char *p1, *p2;

      if (! str || ! *str)
            return str;
      for (p1 = str, p2 = str + strlen(str) - 1; p2 > p1; ++p1, --p2)
      {
            *p1 ^= *p2;
            *p2 ^= *p1;
            *p1 ^= *p2;
      }
      return str;
}
