#ifndef GRAPH_H
#define GRAPH_H

#define XY '*'
#define EMPTY '.'
#define ROWS 25
#define COLMNS 80
#define MID 12
#define M_PI 3.14159265358979323846

char **init_graph();
void drow_graph(char **graph);
void fill_graph(char **graph, char *expression);

#endif
