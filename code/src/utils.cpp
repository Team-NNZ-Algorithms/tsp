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

std::vector<vertex> read_vertices(char* in_file) {
    FILE *fin;
    fin = fopen (in_file, "r");
    assert(fin);

    std::vector<vertex> vertices;
    int x, y;

    while(fscanf( fin, " %*d %d %d\n", &x, &y) == 2) {
        vertices.push_back(vertex{x, y});
    }

    return vertices;
}

struct tsp_problem read_problem(char* in_file) {
    struct tsp_problem new_problem;
    
    new_problem.vertices = read_vertices(in_file);

    for (int i = 0; i < new_problem.vertices.size(); ++i) {
        printf("%d, %d\n", new_problem.vertices[i].x, new_problem.vertices[i].y);
    }
    
    printf("length: %d\n", (int) new_problem.vertices.size());
    return new_problem;
}