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
  std::vector<city*> cities;
  int distance;

  tour() {
      distance = 0;
  }
};

struct tsp_problem {
    std::vector<city> cities;
    std::vector<edge> edges;

    tsp_problem(int num_cities) {
        cities.reserve(num_cities);
        edges.reserve(num_cities * num_cities - num_cities);
    }
};

struct tsp_problem read_problem(char* in_file);
void add_edge_to_tour(struct tour &tour, struct city* next_city, int distance);

void print_tour(struct tour &tour);

#endif
