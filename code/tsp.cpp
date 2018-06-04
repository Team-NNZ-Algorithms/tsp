#include <stdio.h>

#include "src/2-opt.hpp"
#include "src/nearest_neighbor.hpp"
#include "src/utils.hpp"

int main(int argc, char** argv) {
    if( argc < 2 ) {
        printf("Need 1 argument: [input filename]\n");
        return 1;
    }

    char* in_file = argv[1];

    struct tsp_problem problem = read_problem(in_file);

    sort_edges(problem.edges);

    for (int i = 0; i < problem.vertices.size(); ++i) {
        printf("%d, %d\n", problem.vertices[i].x, problem.vertices[i].y);
    }

    for (int i = 0; i < problem.edges.size(); ++i) {
        printf("%d, %d, %d\n", problem.edges[i].start->id, problem.edges[i].end->id, problem.edges[i].weight);
    }
    
    printf("vertices: %d\n", (int) problem.vertices.size());
    printf("edges: %d\n", (int) problem.edges.size());

    return 0;
}