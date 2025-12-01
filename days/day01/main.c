// template.c
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

void part1(FILE* file) {
    // char *content = read_file(file);
    // char **lines = read_lines(file, NULL);
    printf("Part 1 non implementata\n");
}

void part2(FILE* file) { printf("Part 2 non implementata\n"); }

int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Uso: %s <input.txt>\n", argv[0]);
        return 1;
    }

    FILE* file = fopen(argv[1], "r");
    if (!file) {
        perror("Errore apertura file");
        return 1;
    }

    printf("=== Day 01 ===\n");
    part1(file);
    rewind(file);
    part2(file);

    fclose(file);
    return 0;
}
