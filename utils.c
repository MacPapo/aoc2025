#include "utils.h"
#include <errno.h>

char* read_entire_file(const char* filename) {
    FILE* f = fopen(filename, "rb");
    if (!f) {
        perror(filename);
        return NULL;
    }

    fseek(f, 0, SEEK_END);
    long len = ftell(f);
    if (len == -1) {
        perror("ftell");
        fclose(f);
        return NULL;
    }
    fseek(f, 0, SEEK_SET);

    char* buffer = malloc(len + 1);
    if (!buffer) {
        fclose(f);
        return NULL;
    }

    size_t read = fread(buffer, 1, len, f);
    fclose(f);

    if (read != (size_t)len) {
        free(buffer);
        return NULL;
    }
    buffer[len] = '\0';
    return buffer;
}

char** read_lines(const char* filename, int* out_count) {
    char* content = read_entire_file(filename);
    if (!content) return NULL;

    // Conta le righe
    int count = 0;
    for (char* p = content; *p; p++)
        if (*p == '\n') count++;

    if (content[strlen(content) - 1] != '\n') count++; // ultima riga senza \n finale

    // Alloca array di puntatori + 1 per il NULL finale
    char** lines = calloc(count + 1, sizeof(char*));
    if (!lines) {
        free(content);
        return NULL;
    }

    int i = 0;
    char* start = content;
    for (char* p = content;; p++) {
        if (*p == '\n' || *p == '\0') {
            size_t len = p - start;
            char* line = malloc(len + 1);
            if (!line) goto cleanup;
            memcpy(line, start, len);
            line[len] = '\0';
            lines[i++] = line;

            if (*p == '\0') break;
            start = p + 1;
        }
    }
    lines[i] = NULL;

    if (out_count) *out_count = count;
    free(content);
    return lines;

cleanup:
    for (int j = 0; j < i; j++) free(lines[j]);
    free(lines);
    free(content);
    return NULL;
}

void free_lines(char** lines) {
    if (!lines) return;
    for (int i = 0; lines[i]; i++) {
        free(lines[i]);
    }
    free(lines);
}
