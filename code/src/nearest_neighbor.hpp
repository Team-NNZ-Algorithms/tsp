#ifndef NEAREST_NEIGHBOR_HPP
#define NEAREST_NEIGHBOR_HPP

#include "utils.hpp"

void sort_edges(std::vector<edge> &edges);

/*

struct path nearest_neighbor(struct tsp_problem &problem) {
    std::vector<vector> selected_vertices;
    struct path best_path;

    sort_edges(problem.edges);

    while the length of selected_vectors is less than problem.vertices.size():
      find the next edge in problem.edges that doesn't have both connected vertices in selected_vertices
      add that edge to best_path
      if either connected vertex is not in selected_vertices, add it.

    return best_path;
}

*/
#endif