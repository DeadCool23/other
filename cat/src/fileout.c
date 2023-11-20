#include "fileout.h"

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

static void num_line(size_t *line_num, char symb, char prev, const char *flags) {
    if (((strchr(flags, 'n') && !strchr(flags, 'b')) || (strchr(flags, 'b') && symb != '\n')) &&
        prev == '\n') {
        printf("%6zu\t", ++(*line_num));
    }
}

static void tab_message(int *symb) {
    if (*symb == '\t') {
        printf("^");
        *symb += 64;
    }
}

static void end_message(int symb) {
    if (symb == '\n') printf("$");
}

static void special_notation(int *symb) {
    if (*symb > 127 && *symb < 160) printf("M-^");
    if ((*symb < 32 && *symb != '\n' && *symb != '\t') || *symb == 127) printf("^");
    if ((*symb < 32 || (*symb > 126 && *symb < 160)) && *symb != '\n' && *symb != '\t')
        *symb = *symb > 126 ? *symb - 128 + 64 : *symb + 64;
}

static void print_symb(int symb, int *prev, const char *flags, size_t *line_num, bool *eline_printed) {
    if (!(strchr(flags, 's') && *prev == '\n' && symb == '\n' && *eline_printed)) {
        if (*prev == '\n' && symb == '\n')
            *eline_printed = true;
        else
            *eline_printed = false;

        if (strchr(flags, 'n') || strchr(flags, 'b')) num_line(line_num, symb, *prev, flags);
        if (strchr(flags, 'E')) end_message(symb);
        if (strchr(flags, 'T')) tab_message(&symb);
        if (strchr(flags, 'v')) special_notation(&symb);
        fputc(symb, stdout);
    }
    *prev = symb;
}

err_t print_file(const char *file_name, const char *flags, size_t *lines_cnt) {
    err_t err = OK;
    FILE *file = !strcmp(file_name, "-") ? stdin : fopen(file_name, "rt");

    if (file) {
        bool eline_printed = false;
        int symb = fgetc(file), prev = '\n';
        while (symb != EOF) {
            print_symb(symb, &prev, flags, lines_cnt, &eline_printed);
            symb = fgetc(file);
        }
        fclose(file);
    } else
        err = ERR_FILE;
    return err;
}
