#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "libs/err_code.h"
#include "libs/graph/graph_draw.h"
#include "libs/input.h"
#include "libs/polish/polish.h"
#include "libs/stack.h"

int main(void) {
    char *str;
    int err = OK;
    err = input(&str);
    if (err) {
        free(str);
        printf("ERROR: Incorrect input");
        return err;
    }
    char **parse_str;
    err = str_parser(str, &parse_str);
    free(str);
    if (err) {
        if (err == ERR_IO) printf("ERROR: Incorrect input\n");
        if (err == ERR_MEM) printf("ERROR: Memory can't be allocated");
        return err;
    }
    char **polish;
    err = to_polish_note(parse_str, &polish);
    free_data(parse_str);
    if (err) {
        if (err == ERR_IO || err == ERR_SYNTAX) printf("ERROR: Incorrect input\n");
        if (err == ERR_MEM) printf("ERROR: Memory can't be allocated\n");
        return err;
    }

    char graph[HEIGHT][WIDTH];
    graph_init(graph);
    err = graph_draw(graph, polish);
    free_data(polish);
    if (err) {
        if (err == ERR_IO)
            printf("ERROR: Incorrect input\n");
        else
            printf("ERROR: Math expression cant't be calced\n");
        return err;
    }

    graph_print(graph);
    return err;
}