#include "options.h"

#include <ctype.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static char* add_flag(char* flags, const char new_flag) {
    if (strchr(flags, new_flag)) return flags;

    size_t new_length = strlen(flags) + 2;

    char* new_flags = malloc(new_length);

    if (!new_flags) return new_flags;

    sprintf(new_flags, "%s%c", flags, new_flag);
    return new_flags;
}

err_t get_opts(int argc, char** argv, char** flags, size_t* flags_cnt) {
#define OPTS_CNT 9
    int opt, long_index;
    char short_options[OPTS_CNT] = "bensvEtT";
    const struct option long_options[] = {{"number-nonblank", no_argument, 0, 'b'},
                                          {"number", no_argument, 0, 'n'},
                                          {"squeeze-blank", no_argument, 0, 's'},
                                          {0, no_argument, 0, 'e'},
                                          {0, no_argument, 0, 't'},
                                          {0, no_argument, 0, 'T'},
                                          {0, no_argument, 0, 'E'},
                                          {0, no_argument, 0, 'v'},
                                          {0, 0, 0, 0}};

    while ((opt = getopt_long(argc, argv, short_options, long_options, &long_index)) != -1) {
        if (opt == 'e' || opt == 't') {
            *flags = add_flag(*flags, toupper(opt));
            *flags = add_flag(*flags, 'v');
        } else if (opt != '?' && !strchr(*flags, opt)) {
            *flags = add_flag(*flags, opt);
        } else
            return ERR_ARGS;

        if (!*flags) return ERR_MEM;
        (*flags_cnt)++;
    }
    return OK;
}

bool is_opt(char* string) { return (strchr(string, '-') == string) ? true : false; }
