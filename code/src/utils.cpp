#include "utils.hpp"

#include <cmath>
#include <stdio.h>
#include <assert.h>

int vertex_distance(const struct vertex &start, const struct vertex &end) {
    return round(sqrt((start.x - end.x)^2 + (start.y - end.y)^2));
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
    int id, x, y;

    while(fscanf( fin, " %d %d %d\n", &id, &x, &y) == 3) {
        vertices.push_back(vertex{id, x, y});
    }

    return vertices;
}

std::vector<edge> generate_edges(std::vector<vertex> &vertices) {
    std::vector<edge> edges;
    
    for(int i = 0; i < vertices.size(); ++i) {
        for(int j = i + 1; j < vertices.size(); ++j) {
            edges.push_back(edge{
                &vertices[i],
                &vertices[j],
                vertex_distance(vertices[i], vertices[j])
            });
        }
    }

    return edges;
}

struct tsp_problem read_problem(char* in_file) {
    struct tsp_problem new_problem;
    
    new_problem.vertices = read_vertices(in_file);
    new_problem.edges = generate_edges(new_problem.vertices);

    // for (int i = 0; i < new_problem.vertices.size(); ++i) {
    //     printf("%d, %d\n", new_problem.vertices[i].x, new_problem.vertices[i].y);
    // }

    // for (int i = 0; i < new_problem.edges.size(); ++i) {
    //     printf("%d, %d\n", new_problem.edges[i].start->id, new_problem.edges[i].end->id);
    // }
    
    printf("vertices: %d\n", (int) new_problem.vertices.size());
    printf("edges: %d\n", (int) new_problem.edges.size());
    return new_problem;
}