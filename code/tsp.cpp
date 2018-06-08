#include <stdio.h>

#include "src/2-opt.hpp"
#include "src/nearest_neighbor.hpp"
#include "src/utils.hpp"


#if defined(_OPENMP)
#include <omp.h>
#else
#include <time.h>
#endif

int main(int argc, char** argv) {
    printf("\n");

    #if defined(_OPENMP)
    float t = omp_get_wtime();
    #else
    float t = clock();
    #endif
  
    if( argc < 2 ) {
        printf("need 1 argument: [input filename]\n");
        return 1;
    }

    char* in_file = argv[1];

    // read problem from file
    printf("input file: %s\n", in_file);
    struct tsp_problem problem = read_problem(in_file);
    printf("number of cities: %d\n", (int) problem.cities.size());
    printf("number of edges : %d\n\n", (int) (problem.cities.size() * problem.cities.size() - (int) problem.cities.size()));

    // get greedy tour
    #if defined(_OPENMP)
    printf("running nearest neighbor with %d threads\n", omp_get_num_procs());
    #else
    printf("running nearest neighbor with 1 thread\n");
    #endif
    struct tour best_tour = tsp_nearest_neighbor(problem);
    printf("\ngreedy cities visited: %d\n", (int) best_tour.cities.size());
    printf("best greedy distance: %d\n", best_tour.distance);

    // print tour to file
    write_tour(best_tour, in_file);
    
    // print duration
    #if defined(_OPENMP)
    t = omp_get_wtime() - t;
    #else
    t = (clock() - t) / CLOCKS_PER_SEC;
    #endif

    printf("duration: %f\n\n", t);

    return 0;
}
