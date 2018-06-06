#ifndef UTILS_HPP
#define UTILS_HPP

#include <vector>

int city_distance(const struct city &start, const struct city &end);

struct edge;

struct city {
    int id;
    int x, y;
    std::vector<edge> edges;
};

struct edge {
    struct city *start;
    struct city *end;
    int weight;
};

struct tour {
  std::vector<city> cities;
  int distance;
};

struct tsp_problem {
    std::vector<city> cities;
    std::vector<edge> edges;
};

struct tsp_problem read_problem(char* in_file);

#endif
