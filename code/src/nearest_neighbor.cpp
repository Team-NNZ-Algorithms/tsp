#include "nearest_neighbor.hpp"

// adapted from https://en.wikipedia.org/wiki/Nearest_neighbour_algorithm
// asssuming that edges in the problem are already sorted!!!
struct tour tsp_nearest_neighbor( struct tsp_problem &problem ) {
    struct tour best_tour;

    // we will test greedy tours at every starting point
    for( struct city &start : problem.cities ) {

        // this will provide constant time access to see which cities have been visited
        std::vector<bool> current_visited(problem.cities.size(), false);

        // create a new tour and add the first city
        struct tour* current_tour = new struct tour;
        current_tour->cities.push_back(&start);
        current_visited[start.id] = true;

        // while the current_tour is not complete
        while( current_tour->cities.size() < problem.cities.size() ) {

            // starting at the current end of the tour
            struct city* current_city = current_tour->cities.back();
            std::vector<edge>* current_edges = &(current_city->edges);

            // look through the edges for the current city, which are already sorted
            for ( const struct edge &e : *current_edges ) {
                struct city* next_city;

                if ( e.start->id != current_city->id ) {
                    next_city = e.start;
                }
                else {
                    next_city = e.end;
                }

                // if the end isn't visited, visit the end
                if ( !current_visited[next_city->id] ) {
                    add_edge_to_tour(*current_tour, next_city, e.weight);
                    current_visited[next_city->id] = true;
                    break;
                }
            }
        }

	// return to the starting city
	struct city* current_city = current_tour->cities.back();
	std::vector<edge>* current_edges = &(current_city->edges);
	
	for ( const struct edge &e : *current_edges ) {
	  struct city* next_city;

	  // if this edge starts with the current last city in the tour and ends with the first city
	  if ( e.start->id == current_city->id && e.end->id == current_tour->cities[0]->id )
	    {
	      // add first city edge, completing the tour
	      next_city = e.end;
	      add_edge_to_tour(*current_tour, next_city, e.weight);
	      break;
	    }
	  // or if they're in the reverse order
	  else if ( e.start->id == current_tour->cities[0]->id && e.end->id == current_city->id ) {
	      next_city = e.start;
	      add_edge_to_tour(*current_tour, current_tour->cities[0], e.weight);
	      break;
	  }
	}
	
        print_tour(*current_tour);

        // change best_tour if this current tour is better.
        if( current_tour->distance < best_tour.distance ) {
            print_tour(*current_tour);
            best_tour = *current_tour;
        }

        delete current_tour;
    }

    return best_tour;
}
