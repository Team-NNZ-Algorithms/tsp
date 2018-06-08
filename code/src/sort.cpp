#include "sort.hpp"
#include "utils.hpp"
#include <algorithm>
#include <stdio.h>

// comparison function for edges
bool edge_compare(const edge &a, const edge &b) {
    return (a.weight <= b.weight);
}

/*

args: a integer vector
returns: none

sources: Introduction to Algorithm. 3rd edition. By Thomas,H, Carmen and others.
         http://www.geeksforgeeks.org/quick-sort/
 **/

void quick_sort(std::vector<edge>& arr) {
    int low = 0;                // index of first element
    int high = arr.size() - 1;  // index of last element

    quick_sort_recursive(arr, low, high);
}

/*****************************************************************************
 Helper function partition
*****************************************************************************/
int partition(std::vector<edge>& arr, int low, int high) {
    edge pivot = arr[high];  // pivot is the last element
    int j = low;            // set j to the first element
    int i = low - 1;         

    // let j iterate through all element before pivot
    for (j = low; j <= high - 1; j++) {

      // if array[j] is <= pivot
      //if (arr[j] <= pivot) {
      if (edge_compare(arr[j], pivot)) {
            // increment i and swap ith and jth element
            i++;
            std::swap(arr[i], arr[j]);
        }
    }

    // swap the i+1 element and last element
    std::swap(arr[i + 1], arr[high]);

    return i + 1;
}

/*****************************************************************************
 Helper function quick_sort_recursive
*****************************************************************************/
void quick_sort_recursive(std::vector<edge>& arr, int low, int high) {
    if (low < high) {
        // set pivot
        int pivot = partition(arr, low, high);

        // perform quick sort recursively on the lower half
        quick_sort_recursive(arr, low, pivot - 1);

        // perform quick sort recursively on the higher half
        quick_sort_recursive(arr, pivot + 1, high);
    }
}

void sort_edges(std::vector<edge> &edges) {
    
  // mergeSort(edges, 0, edges.size() - 1);
  quick_sort(edges);
}
