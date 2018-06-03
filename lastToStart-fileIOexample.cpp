#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <limits>
using namespace std;

// Eric Newton
// CS325-400
// C++ implementation of selectLastStart
// With help from CRLS p.421, Greedy-Activity-Selector Pseudocode
// And https://www.uow.edu.au/~lukes/TEXTBOOK/notes-cpp/io/readtextfile.html for file IO
// http://www.augustcouncil.com/~tgibson/tutorial/iotips.html

struct Activity {
  int number;
  int start;
  int finish;
};

void printArray(int array[], int length);
// Merge prototype
void merge(Activity arr[], int l, int mid, int r);

// Greedy Last Start Activity Selector
// Takes an array of activites already sorted by last start time (descending order) and the length of that array
// Outputs to the terminal the number of activities selected and their order
void selectLastStart(Activity arr[], int length)
{
  // Don't need the results for this particular problem, could use and return a vector here
  // And get rid of the scheduledActivites array as a result
  Activity results[length];

  // Array keeping track of which activity #s have been scheduled
  int scheduledActivities[length];
 
  // Add the initial Activity with the latest start time
  results[0] = arr[0];
  scheduledActivities[0] = arr[0].number;
  
  int k = 0;  // Index of last scheduled activity
  int numSelected = 1; // Number of activities we've selected
  
  // Iterate through all remaining activities
  for(int i = 1; i < length; i++) {
    // If the finish time of this activity is less than or equal to the already scheduled start time
    if(arr[i].finish <= arr[k].start) {
      results[i] = arr[i]; // Add it to the set
      k = i; // Update last scheduled index

      // Keep track of which # activities we've scheduled and how many
      scheduledActivities[numSelected] = arr[i].number;
      numSelected++;
    }
  }
  
  cout << "Number of activities selected = " << numSelected << endl;
  cout << "Activities: ";

  // Print the activities in order of time (opposite of how we selected them)
  for (int i = numSelected-1; i >= 0; i--)
    cout << scheduledActivities[i] << " ";

  cout << endl << endl;
}

// mergeSort
// Takes the array, left index and right index
// Merges two subarrays of the passed array
// First is arr[l..r]
// Second is arr[mid+1..r]
void mergeSortStartTimes(Activity arr[], int l, int r) {
  if (l < r)
    {
      int mid = l+(r-l)/2; // Equivalent to (l+r)/2, for very large values of l and r

      // Left array recursion
      mergeSortStartTimes(arr, l, mid);

      // Right array recursion
      mergeSortStartTimes(arr, mid+1, r);

      // Merge the two subarrays
      merge(arr, l, mid, r);
    }
}

// merge
// Takes the array, left, mid, and right index
// Merges the two arrays arr[l..r] and arr[mid+1..r]
void merge(Activity arr[], int l, int mid, int r) {
  int i, j, k; // Indexes for merging
  int n1 = mid - l + 1; // First array # of elements
  int n2 = r - mid; // Second array # of elements

  // Create temporary arrays
  Activity L[n1], R[n2];

  // Copy data to them
  for (i = 0; i < n1; i++)
    L[i] = arr[l+i];
  for (j = 0; j < n2; j++)
    R[j] = arr[mid + 1 + j];

  // Merge them back into arr[l..r]
  i = 0; // Initial index of first subarray
  j = 0; // Initial index of second subarray
  k = l; // Initial index of merged array

  // Compare the elements of each subarray, placing the smaller element in the merged array
  // While we don't exceed the # of elements of each subarray
  while (i < n1 && j < n2)
    {
      // If left element is smaller or equal
      if (L[i].start >= R[j].start)
	{
	  // Place in merged array
	  arr[k] = L[i];
	  i++;
	}
      else
	{
	  // Otherwise place right element in merged array
	  arr[k] = R[j];
	  j++;
	}

      // Move to next element in merged array
      k++;
    }

  // Copy any remaining elements of L[] if any
  while (i < n1)
    {
      arr[k] = L[i];
      i++;
      k++;
    }

  // Copy any remaining elements of R[] if any
  while (j < n2)
    {
      arr[k] = R[j];
      j++;
      k++;
    }
}

// Mainly contains file I/O
int main()
{
  ifstream inputFile;
  ofstream outputFile;
  
  string line; // Temporary variable for reading in lines
  int activitiesNum; // The number of activities in a given set
  int setNum = 1; // The number of this set

  inputFile.open("act.txt");
  
  if (!inputFile || !outputFile) {
    cout << "Error! Unable to open file.";
    exit(1);
  }

   // While the end of file is not reached
  while(!inputFile.eof()) {

    // Get the string of the first value, the number of activities in the set
    getline(inputFile, line);
  
    // Process the line string as a stream
    stringstream lineStream(line);
    string currentVal;

    // # of activites in the set
    lineStream >> currentVal;
    
    activitiesNum = stoi(currentVal); // Convert to number

    // Create the array of size # of activities
    Activity array[activitiesNum];
    int length = activitiesNum; // Length of the array
   
    int i = 0;
  
    // Process this set
    while (activitiesNum != 0) {
      // Get the next line
      lineStream.clear();
    
      getline(inputFile, line);
      lineStream.str(line);
     
      // While still reading from the line stream
      // Continue reading string
      // Three values
      lineStream >> currentVal; // activity #
      array[i].number = stoi(currentVal);
      
      lineStream >> currentVal; // start time
      array[i].start = stoi(currentVal);
					      
      lineStream >> currentVal; // finish time
      array[i].finish = stoi(currentVal);
        
      activitiesNum--;
      i++;
    }

    // Sort activities by last start time
    mergeSortStartTimes(array, 0, length-1);

    // Select activities by last start time
    cout << "Set " << setNum << endl;
    selectLastStart(array, length);
    setNum++;
  }
  
  inputFile.close();

  return 0;
}
