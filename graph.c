#include "graph.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "rpn.h"
#include "stacks.h"
#include "utils.h"

int main() {
    char **graph = init_graph();
    if (graph == NULL) {
        printf("n/a");
        return 1;
    }
    printf("Enter expression: ");
    char expression[1024];
    scanf("%1024s", expression);
    oper_replace(expression);
    printf("%s", expression);
    if (is_allowed(expression) != 0) {
        printf("n/a");
        return 1;
    }
    printf("\e[1;1H\e[2J");
    fill_graph(graph, expression);
    drow_graph(graph);
    for (int r = 0; r < ROWS; r++) {
        free(graph[r]);
    }
    free(graph);
    return 0;
}

char **init_graph() {
    char **graph = malloc(ROWS * sizeof(char *));
    if (graph == NULL) {
        printf("Error\n");
        exit(1);
    }
    for (int r = 0; r < ROWS; r++) {
        graph[r] = malloc(COLMNS * sizeof(char));
        for (int c = 0; c < COLMNS; c++) {
            graph[r][c] = EMPTY;
        }
    }
    return graph;
}

void fill_graph(char **graph, char *expression) {
    int count = 0;
    for (double x = 0; x <= 4.0 * M_PI; x += 4.0 * M_PI / 80.0) {
        double res = calc_expression(expression, x);
        int y = (int)round(res * MID);
        if (y <= MID && y >= -MID) {
            graph[MID - y][count] = XY;
        }
        count++;
    }
}

void drow_graph(char **graph) {
    printf("================================================================================\n");
    for (int r = 0; r < ROWS; r++) {
        for (int c = 0; c < COLMNS; c++) {
            (c == COLMNS - 1 && r != ROWS - 1) ? (printf("%c\n", graph[r][c])) : (printf("%c", graph[r][c]));
        }
    }
    printf("\n");
    printf("================================================================================\n");
}
