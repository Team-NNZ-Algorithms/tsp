#ifndef UTILS_HPP
#define UTILS_HPP

#include <vector>

struct vertex {
    int x, y;
};

struct edge {
    struct vertex *start;
    struct vertex *end;
    int weight;
};

struct tsp_problem {
    std::vector<vertex> vertices;
    std::vector<edge> edges;
};

struct tsp_problem read_problem(char* in_file);

#endif