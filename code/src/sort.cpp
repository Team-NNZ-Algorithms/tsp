#include "sort.hpp"
#include "utils.hpp"
#include <algorithm>
#include <stdio.h>

bool edge_sort (const edge &a, const edge &b) {
    return (a.weight < b.weight);
}

void sort_edges(std::vector<edge> &edges) {
    
  // std::sort(edges.begin(), edges.end(), edge_sort);
  mergeSort(edges, 0, edges.size() - 1);
}

// mergeSort
// Takes the vector, left index and right index
// Merges two subarrays of the passed vector
// First is vec[l..r]
// Second is vec[mid+1..r]
void mergeSort(std::vector<edge> &vec, int l, int r) {
  if (l < r)
    {
      int mid = l+(r-l)/2; // Equivalent to (l+r)/2, for very large values of l and r

      // Left array recursion
      mergeSort(vec, l, mid);

      // Right array recursion
      mergeSort(vec, mid+1, r);

      // Merge the two subarrays
      merge(vec, l, mid, r);
    }
}

// merge
// Takes the vector, left, mid, and right index
// Merges the two arrays vec[l..r] and vec[mid+1..r]
void merge(std::vector<edge> &vec, int l, int mid, int r) {
  int i, j, k; // Indexes for merging
  int n1 = mid - l + 1; // First array # of elements
  int n2 = r - mid; // Second array # of elements

  // Create temporary arrays of edges
  edge L[n1], R[n2];

  // Copy data to them
  for (i = 0; i < n1; i++)
    L[i] = vec[l+i];
  for (j = 0; j < n2; j++)
    R[j] = vec[mid + 1 + j];

  // Merge them back into vec[l..r]
  i = 0; // Initial index of first subarray
  j = 0; // Initial index of second subarray
  k = l; // Initial index of merged array

  // Compare the elements of each subarray, placing the smaller element in the merged array
  // While we don't exceed the # of elements of each subarray
  while (i < n1 && j < n2)
    {
      // If left element is smaller or equal
      // (a.weight < b.weight);
      if (L[i].weight <= R[j].weight)
	{
	  // Place in merged array
	  vec[k] = L[i];
	  i++;
	}
      else
	{
	  // Otherwise place right element in merged array
	  vec[k] = R[j];
	  j++;
	}

      // Move to next element in merged array
      k++;
    }

  // Copy any remaining elements of L[] if any
  while (i < n1)
    {
      vec[k] = L[i];
      i++;
      k++;
    }

  // Copy any remaining elements of R[] if any
  while (j < n2)
    {
      vec[k] = R[j];
      j++;
      k++;
    }
}
