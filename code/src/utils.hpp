#ifndef UTILS_HPP
#define UTILS_HPP

struct vertex {
    int id;
    int x, y;
};

struct edge {
    struct vertex *start;
    struct vertex *end;
    int weight;
};

struct tsp_problem {
    struct vertex *vertices;
    struct edge *edges;
};

struct tsp_problem read_problem(char* in_file);

#endif