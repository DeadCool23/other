#include "input.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "err_code.h"

int input(char **exp) {
    size_t size = 0;
    *exp = (char *)calloc(size, sizeof(char));
    if (*exp == NULL) return ERR_MEM;
    do {
        *exp = realloc(*exp, (++size) * sizeof(char));
        if (*exp == NULL) return ERR_MEM;
        (*exp)[size - 1] = getc(stdin);
    } while ((*exp)[size - 1] != '\n');
    (*exp)[size - 1] = '\0';
    return !strlen(*exp) ? ERR_IO : OK;
}