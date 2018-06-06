#include "2-opt.hpp"
#include "utils.hpp"

struct tour swap(struct tour tour, int i, int k);

void checkTourDistance(struct tour &tour)
{
  int bestDistance = tour.distance;
  struct tour newTour;
  
  for (int i = 0; i < tour.cities.size() - 1; i++) {
    for (int k = i + 1; k < tour.cities.size(); k++) {
      newTour = swap(tour, i, k);
      
      if(newTour.distance < bestDistance) {

	// best tour = new tour
	tour.cities.swap(newTour.cities);
	tour.distance = newTour.distance;
	//tour.numEdges = newTour.numEdges;
	
	bestDistance = newTour.distance;
	// goto start_again
      }
      
    }
  }
}

struct tour swap(struct tour tour, int i, int k)
{
  struct tour newTour;
  int newDistance = 0;

  //    1. take route[0] to route[i-1] and add them in order to new_route
  for (int m = 0; m <= i-1; i++)
    newTour.cities.push_back(tour.cities[i]);
  
  //    2. take route[i] to route[k] and add them in reverse order to new_route
  for (int n = k; n >= i; n--)
    newTour.cities.push_back(tour.cities[n]);
    
  //    3. take route[k+1] to end and add them in order to new_route
  for (int p = k+1; p < tour.cities.size(); p++)
    newTour.cities.push_back(tour.cities[p]);

  // Calculate the new tour's distance
  for (int l = 0; l < newTour.cities.size() - 1; l++)
    newDistance += vertex_distance(newTour.cities[l], newTour.cities[l+1]);

  newTour.distance = newDistance;
  
  //    return new_route;
  return newTour;
}
