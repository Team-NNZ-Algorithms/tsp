#include "utils.hpp"

#include <cmath>
#include <stdio.h>
#include <assert.h>

int vertex_distance(struct vertex *start, struct vertex *end) {
    return round(sqrt((start->x - end->x)^2 + (start->y - end->y)^2));
}

int total_vertices(char* in_file) {
    FILE *fin;
    fin = fopen (in_file, "r");
    assert(fin);

    int num_lines = 0;

    while(fscanf( fin, " %*d %*d %*d\n") == 0) {
        ++num_lines;
    }

    return num_lines;
}

struct tsp_problem read_problem(char* in_file) {
    struct tsp_problem new_problem;
    
    printf("%d\n", total_vertices(in_file));

    return new_problem;
}