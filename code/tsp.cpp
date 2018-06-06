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

    for (int i = 0; i < problem.cities.size(); ++i) {
        printf("%d, %d\n", problem.cities[i].x, problem.cities[i].y);
    }

    for (int i = 0; i < problem.edges.size(); ++i) {
        printf("%d, %d, %d\n", problem.edges[i].start->id, problem.edges[i].end->id, problem.edges[i].weight);
    }
    
    printf("cities: %d\n", (int) problem.cities.size());
    printf("edges: %d\n", (int) problem.edges.size());

    return 0;
}