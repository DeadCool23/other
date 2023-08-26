#include "graph_draw.h"

#define _USE_MATH_DEFINES

#include <math.h>
#include <stdio.h>

#ifndef M_PI
#define M_PI (3.14159265358979323846)
#endif

#include "../err_code.h"
#include "../polish/polish.h"

void graph_init(char graph[][WIDTH]) {
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            graph[y][x] = '.';
        }
    }
}

int graph_draw(char graph[][WIDTH], char **polish) {
    for (double x = 0; x <= 4 * M_PI; x += 0.1) {
        int err = OK;
        double y = polish_calc(polish, &err, x);
        if (err) return err;

        int screenX = round(x / (4 * M_PI) * (WIDTH - 1));
        int screenY = round((1 - y) / 2 * (HEIGHT - 1));

        if ((screenX >= 0 && screenX < WIDTH) && (screenY >= 0 && screenY < HEIGHT))
            graph[screenY][screenX] = '*';
    }
    return OK;
}

void graph_print(char graph[][WIDTH]) {
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            printf("%c", graph[y][x]);
        }
        printf("\n");
    }
}
