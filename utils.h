#ifndef UTILS_H
#define UTILS_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Legge l'intero file e restituisce una stringa mallocata con terminatore \0.
   Il chiamante DEVE liberarla con free(). */
char* read_entire_file(const char* filename);

/* Legge tutte le righe del file.
   Restituisce un array di stringhe (char**) terminato da NULL.
   Ogni riga ha il \n rimosso, ma è ancora mallocata.
   Il chiamante deve liberare tutto con free_lines(). */
char** read_lines(const char* filename, int* out_count);

/* Libera l'array di righe restituito da read_lines() */
void free_lines(char** lines);

/* Versione comoda: legge il file e lo splitta in righe già pronte all'uso */
#define READ_LINES(fname, lines_ptr, count_ptr)                                                    \
    do {                                                                                           \
        *(lines_ptr) = read_lines((fname), (count_ptr));                                           \
        if (!*(lines_ptr)) {                                                                       \
            fprintf(stderr, "Errore lettura %s\n", (fname));                                       \
            exit(1);                                                                               \
        }                                                                                          \
    } while (0)

#endif // UTILS_H
