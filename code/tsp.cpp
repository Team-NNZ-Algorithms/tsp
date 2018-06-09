#include <stdio.h>
#include <time.h>

#include "src/2-opt.hpp"
#include "src/nearest_neighbor.hpp"
#include "src/utils.hpp"

#if defined(_OPENMP)
#include <omp.h>
#endif

int main(int argc, char** argv) {
    printf("\n");
    struct timespec start, finish;
    double elapsed;

    clock_gettime(CLOCK_MONOTONIC, &start);
  
    if( argc < 2 ) {
        printf("need 1 argument: [input filename]\n");
        return 1;
    }

    char* in_file = argv[1];

    // read problem from file
    printf("input file: %s\n", in_file);
    struct tsp_problem problem = read_problem(in_file);
    printf("number of cities: %d\n", (int) problem.cities.size());
    printf("number of edges : %d\n", (int) (problem.cities.size() * problem.cities.size() - (int) problem.cities.size()));

    // print time for setup
    clock_gettime(CLOCK_MONOTONIC, &finish);
    elapsed = (finish.tv_sec - start.tv_sec);
    elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
    printf("time for setup  : %.4fs\n\n", elapsed);

    // get nearest neighbor greedy tour
    #if defined(_OPENMP)
    printf("running nearest neighbor with %d threads\n", omp_get_num_procs());
    #else
    printf("running nearest neighbor with 1 thread\n");
    #endif

    struct tour best_tour = tsp_nearest_neighbor(problem);
    int greedy_distance = best_tour.distance;
    printf("best greedy distance : %d\n", best_tour.distance);
    clock_gettime(CLOCK_MONOTONIC, &finish);
    elapsed = (finish.tv_sec - start.tv_sec);
    elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
    printf("duration after greedy: %.4fs\n\n", elapsed);

    printf("running 2-opt with 1 thread\n");
    two_opt(best_tour, problem);
    int two_opt_distance = best_tour.distance;
    printf("2-opt distance   : %d\n", best_tour.distance);
    printf("2-opt improvement: %.2f%%\n", (float) greedy_distance / two_opt_distance - 1);
    clock_gettime(CLOCK_MONOTONIC, &finish);
    elapsed = (finish.tv_sec - start.tv_sec);
    elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
    printf("total duration   : %.4fs\n\n", elapsed);

    // print tour to file
    write_tour(best_tour, in_file);

    return 0;
}
