#include "sort.hpp"
#include "utils.hpp"

bool edge_sort (const edge &a, const edge &b) {
    return (a.weight < b.weight);
}

void sort_edges(std::vector<edge> &edges) {
    std::sort(edges.begin(), edges.end(), edge_sort);
}