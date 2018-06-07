#ifndef SORT_HPP
#define SORT_HPP

#include <vector>

struct edge;

void merge(std::vector<edge> vec, int l, int mid, int r);
void mergeSort(std::vector<edge> vec, int l, int r);

bool edge_sort(const edge &a, const edge &b);
void sort_edges(std::vector<edge> &edge);

#endif
