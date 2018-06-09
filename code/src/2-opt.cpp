#include "2-opt.hpp"
#include "utils.hpp"

#include <stdio.h>
#include <time.h>

struct tour two_opt_swap(const struct tour &tour, int i, int k, const struct tsp_problem &problem)
{
    struct tour newTour(problem.cities.size());

    // 1. take route[0] to route[i-1] and add them in order to new_route
    for( int m = 0; m <= i - 1; ++m )
        add_city_to_tour(newTour, tour.cities[m], problem);
    
    // 2. take route[i] to route[k] and add them in reverse order to new_route
    for( int m = k; m >= i; --m )
        add_city_to_tour(newTour, tour.cities[m], problem);
      
    // 3. take route[k+1] to end and add them in order to new_route
    for( unsigned m = k+1; m < tour.cities.size(); ++m )
        add_city_to_tour(newTour, tour.cities[m], problem);

    // 4. finish by returning to start
    complete_tour(newTour, problem);
    
    // return new_route;
    return newTour;
}

void two_opt(struct tour &tour, struct tsp_problem &problem)
{
    struct timespec start_time, finish_time;
    double elapsed;
    clock_gettime(CLOCK_MONOTONIC, &start_time);

    start_over:
    int bestDistance = tour.distance;
  
    for( unsigned i = 1; i < tour.cities.size() - 1; ++i ) {
        clock_gettime(CLOCK_MONOTONIC, &finish_time);
        elapsed = (finish_time.tv_sec - start_time.tv_sec);
        elapsed += (finish_time.tv_nsec - start_time.tv_nsec) / 1000000000.0;

        if ( elapsed < 240 ) {
            for( unsigned k = i + 1; k < tour.cities.size(); ++k ) {
                struct tour newTour = two_opt_swap(tour, i, k, problem);
                
                if( newTour.distance < bestDistance ) {
                    clock_gettime(CLOCK_MONOTONIC, &finish_time);
                    elapsed = (finish_time.tv_sec - start_time.tv_sec);
                    elapsed += (finish_time.tv_nsec - start_time.tv_nsec) / 1000000000.0;
                    printf("new best: %d, elapsed: %.4f\n", newTour.distance, elapsed);
                    tour.cities.swap(newTour.cities);
                    tour.distance = newTour.distance;
            
                    bestDistance = newTour.distance;

                    goto start_over;
                }
            }
        }
    }

    printf("\n");
}
