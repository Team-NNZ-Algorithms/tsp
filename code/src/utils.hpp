#ifndef UTILS_HPP
#define UTILS_HPP

#include <vector>

int city_distance(const struct city &start, const struct city &end);

struct city {
    int id;
    int x, y;
};

struct tour {
  std::vector<city*> cities;
  std::vector<bool> visited;
  int distance;

  tour(int num_cities) {
      distance = 0;
      visited.assign(num_cities, false);
  }
};

struct tsp_problem {
    std::vector<city> cities;
    std::vector<int> adjacency;
};

struct tsp_problem read_problem(char* in_file);
void add_city_to_tour(struct tour &tour, struct city* next_city, int distance);
void print_tour(struct tour &tour);
int matrix_index(int row, int column, int row_size);
void complete_tour(struct tour &tour, std::vector<int>& adjacency);
void write_tour(struct tour &best_tour, char* in_file);

#endif
