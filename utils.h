#ifndef UTILS_H
#define UTILS_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

char* slurp_file(FILE* f);
char** read_all_lines(FILE* f, int* out_count, bool skip_empty);
void free_lines(char** lines);

#define READ_ALL_LINES(fp, lines, count, skip_empty)                                               \
    do {                                                                                           \
        (lines) = read_all_lines((fp), &(count), (skip_empty));                                    \
        if (!(lines)) {                                                                            \
            fprintf(stderr, "Errore lettura input\n");                                             \
            exit(EXIT_FAILURE);                                                                    \
        }                                                                                          \
    } while (0)

#endif
