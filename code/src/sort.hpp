#ifndef SORT_HPP
#define SORT_HPP

#include <vector>

struct edge;

bool edge_sort(const edge &a, const edge &b);
void sort_edges(std::vector<edge> &edge);

#endif