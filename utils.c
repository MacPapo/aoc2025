#include "utils.h"
#include <string.h>

char* slurp_file(FILE* f) {
    if (fseek(f, 0, SEEK_END) != 0) return NULL;
    long len = ftell(f);
    if (len < 0) return NULL;
    if (fseek(f, 0, SEEK_SET) != 0) return NULL;

    char* buf = malloc((size_t)len + 1);
    if (!buf) return NULL;

    size_t n = fread(buf, 1, (size_t)len, f);
    if (n != (size_t)len) {
        free(buf);
        return NULL;
    }

    buf[len] = '\0';
    return buf;
}

// to
char** read_all_lines(FILE* f, int* out_count, bool skip_empty) {
    char* content = slurp_file(f);
    if (!content) return NULL;

    size_t cap = 16;
    size_t count = 0;

    char** lines = malloc(cap * sizeof(char*));
    if (!lines) {
        free(content);
        return NULL;
    }

    char* start = content;
    char* p = content;

    while (*p) {
        if (*p == '\n') {
            size_t len = p - start;

            if (!(skip_empty && len == 0)) {
                char* line = malloc(len + 1);
                if (!line) goto cleanup;
                memcpy(line, start, len);
                line[len] = '\0';

                if (count == cap) {
                    cap *= 2;
                    char** tmp = realloc(lines, cap * sizeof(char*));
                    if (!tmp) goto cleanup;
                    lines = tmp;
                }
                lines[count++] = line;
            }

            start = p + 1;
        }
        p++;
    }

    if (start < p) {
        size_t len = p - start;
        if (!(skip_empty && len == 0)) {
            char* line = malloc(len + 1);
            if (!line) goto cleanup;
            memcpy(line, start, len);
            line[len] = '\0';

            if (count == cap) {
                cap *= 2;
                char** tmp = realloc(lines, cap * sizeof(char*));
                if (!tmp) goto cleanup;
                lines = tmp;
            }
            lines[count++] = line;
        }
    }

    lines[count] = NULL;
    if (out_count) *out_count = (int)count;

    free(content);
    return lines;

cleanup:
    for (size_t i = 0; i < count; i++) free(lines[i]);
    free(lines);
    free(content);
    return NULL;
}

void free_lines(char** lines) {
    if (!lines) return;
    for (size_t i = 0; lines[i]; i++) free(lines[i]);
    free(lines);
}
