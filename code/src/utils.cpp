#include "utils.hpp"
#include "sort.hpp"

#include <cmath>
#include <stdio.h>
#include <assert.h>

int city_distance(const struct city &start, const struct city &end) {
    return round(sqrt((start.x - end.x)*(start.x - end.x) + (start.y - end.y)*(start.y - end.y)));
}

int total_cities(char* in_file) {
    FILE *fin;
    fin = fopen (in_file, "r");
    assert(fin);

    int num_lines = 0;

    while(fscanf( fin, " %*d %*d %*d\n") == 0) {
        ++num_lines;
    }

    return num_lines;
}

std::vector<city> read_cities(char* in_file) {
    FILE *fin;
    fin = fopen (in_file, "r");
    assert(fin);

    std::vector<city> cities;
    int id, x, y;

    while(fscanf( fin, " %d %d %d\n", &id, &x, &y) == 3) {
        cities.push_back(city{id, x, y});
    }

    return cities;
}

std::vector<edge> generate_edges(std::vector<city> &cities) {
    std::vector<edge> edges;
    
    for(int i = 0; i < cities.size(); ++i) {
        for(int j = i + 1; j < cities.size(); ++j) {
            edges.push_back(edge{
                &cities[i],
                &cities[j],
                city_distance(cities[i], cities[j])
            });
        }
    }

    return edges;
}

struct tsp_problem read_problem(char* in_file) {
    struct tsp_problem new_problem;
    
    new_problem.cities = read_cities(in_file);
    new_problem.edges = generate_edges(new_problem.cities);

    sort_edges(new_problem.edges);

    for(struct edge &e: new_problem.edges) {
        e.start->edges.push_back(e);
        e.end->edges.push_back(e);
    }

    return new_problem;
}
