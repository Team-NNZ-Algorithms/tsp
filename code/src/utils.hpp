#ifndef UTILS_HPP
#define UTILS_HPP

#include <vector>

int vertex_distance(const struct vertex &start, const struct vertex &end);

struct vertex {
    int id;
    int x, y;
};

struct edge {
    struct vertex *start;
    struct vertex *end;
    int weight;
};

struct tour {
  std::vector<vertex> cities;
  int distance;
  int numEdges;
};

struct tsp_problem {
    std::vector<vertex> vertices;
    std::vector<edge> edges;
};

struct tsp_problem read_problem(char* in_file);

#endif
