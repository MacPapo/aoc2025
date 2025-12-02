#include "utils.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define START_POS 50
#define MOD(a, m) (((a) % (m) + (m)) % (m))

const int ncomb = 100;

static int parse_value(const char* line) {
    int sign = (line[0] == 'R') ? 1 : -1;
    return sign * atoi(line + 1);
}

void part1(FILE* file) {
    char** lines;
    int nlines, pos = START_POS, clicks = 0;

    printf("\n==Part 1==\n");
    READ_ALL_LINES(file, lines, nlines, true);

    for (int i = 0; lines[i]; i++) {
        int delta = parse_value(lines[i]);
        pos = MOD(pos + delta, ncomb);
        if (pos == 0) clicks++;
    }

    printf("SOL: %d\n===\n", clicks);
    free_lines(lines);
}

void part2(FILE* file) {
    char** lines;
    int nlines, pos = START_POS, clicks = 0;

    printf("\n==Part 2==\n");
    READ_ALL_LINES(file, lines, nlines, true);

    for (int i = 0; lines[i]; i++) {
        int delta = parse_value(lines[i]);

        int npos = pos + delta;
        if (npos < 0 || npos > 99) {
            printf("entrato\t");
        }
        printf("NUM: %d\tDEL: %d\tPOS: %d\n", pos, delta, npos);

        pos = MOD(npos, ncomb);
    }

    printf("SOL: %d\n===\n", clicks);
    free_lines(lines);
}

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
