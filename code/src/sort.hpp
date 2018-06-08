#ifndef SORT_HPP
#define SORT_HPP

#include <vector>

struct edge;

//quick_sort function
void quick_sort(std::vector<edge>&);

//helper functions
int partition(std::vector<edge>&, int, int);
void quick_sort_recursive(std::vector<edge>&, int, int);

void sort_edges(std::vector<edge> &edge);

#endif
