#include "nearest_neighbor.hpp"

/*

struct path nearest_neighbor(struct tsp_problem &problem) {
    std::vector<city> selected_cities;
    struct path best_path;

    sort_edges(problem.edges);

    while the length of selected_vectors is less than problem.cities.size():
      find the next edge in problem.edges that doesn't have both connected cities in selected_cities
      add that edge to best_path
      if either connected city is not in selected_cities, add it.

    return best_path;
}

*/