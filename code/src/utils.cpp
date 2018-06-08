#include "utils.hpp"
// #include "sort.hpp"

#include <cmath>
#include <stdio.h>
#include <assert.h>

// calculate the distance between two cities
int city_distance(const struct city &start, const struct city &end) {
    return round(sqrt((start.x - end.x)*(start.x - end.x) + (start.y - end.y)*(start.y - end.y)));
}

// read cities in from file
std::vector<city> read_cities(char* in_file) {
    FILE *fin;
    fin = fopen (in_file, "r");
    assert(fin);

    std::vector<city> cities;
    int id, x, y;

    while(fscanf( fin, " %d %d %d\n", &id, &x, &y) == 3) {
        cities.push_back(city{id, x, y});
    }

    fclose (fin);
    
    return cities;
}

// used to fake a 2D matrix from a 1D array
int matrix_index(int row, int column, int row_size) {
    return row * row_size + column;
}

// generate the adjacencies for the cities in a given problem
void generate_adjacencies(struct tsp_problem& problem) {
    int num_edges = problem.cities.size() * problem.cities.size();
    problem.adjacency.assign(num_edges, std::numeric_limits<int>::max());

    for(int i = 0; i < problem.cities.size(); ++i) {
        for(int j = 0; j < problem.cities.size(); ++j) {
            int index = matrix_index(i, j, problem.cities.size());
            if( i != j ) {
                problem.adjacency[index] = city_distance(problem.cities[i], problem.cities[j]);
            }
        }
    }

}

// constructs a problem from the file
struct tsp_problem read_problem(char* in_file) {
    struct tsp_problem new_problem;
    
    new_problem.cities = read_cities(in_file);
    generate_adjacencies(new_problem);

    return new_problem;
}

// adds a city to the tour and re-calculates the distance
void add_city_to_tour(struct tour &tour, struct city* next_city, int distance) {
    tour.cities.push_back(next_city);
    tour.visited[next_city->id] = true;
    tour.distance += distance;
}

// adds the final leg of the tour
void complete_tour(struct tour &tour, std::vector<int>& adjacency) {
    int index = matrix_index(tour.cities.front()->id, tour.cities.back()->id, tour.cities.size());
    tour.distance += adjacency[index];
}

// prints out debug info about the tour
void print_tour(struct tour &tour) {
    for (const city *c : tour.cities) {
        printf("city: %d\n", c->id);
    }

    printf("visited cities: %d\n", (int) tour.cities.size());
    printf("distance: %d\n", tour.distance);
}