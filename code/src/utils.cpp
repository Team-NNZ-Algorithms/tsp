#include "utils.hpp"
#include <cmath>

int vertex_distance(struct vertex *start, struct vertex *end) {
    return round(sqrt((start->x - end->x)^2 + (start->y - end->y)^2));
}

struct tsp_problem read_problem(char* in_file) {
    struct tsp_problem new_problem;



    return new_problem;
}