#include <stdio.h>

#include "src/2-opt.hpp"
#include "src/nearest_neighbor.hpp"
#include "src/utils.hpp"

#include <time.h>

int main(int argc, char** argv) {
    printf("\n");

    clock_t t;
    t = clock();
  
    if( argc < 2 ) {
        printf("Need 1 argument: [input filename]\n");
        return 1;
    }

    char* in_file = argv[1];
    printf("Input file: %s\n", in_file);

    // read problem from file
    struct tsp_problem problem = read_problem(in_file);
    printf("number of cities: %d\n\n", (int) problem.cities.size());

    // get greedy tour
    struct tour best_tour = tsp_nearest_neighbor(problem);
    printf("greedy cities visited: %d\n", (int) best_tour.cities.size());
    printf("best greedy distance: %d\n", best_tour.distance);

    // print duration
    t = clock() - t;
    printf("Duration: %f\n\n", ((float)t)/CLOCKS_PER_SEC);

    return 0;
}
