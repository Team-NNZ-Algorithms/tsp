// Eric Newton
// CS325-400
// HW#5
// Help from https://www.geeksforgeeks.org/graph-and-its-representations/ for graph implementation 
// https://www.geeksforgeeks.org/bfs-disconnected-graph/ for handling disconnected graphs

#include<fstream>
#include<sstream>
#include<iostream>
#include<vector>
#include<queue>
#include<list>

using namespace std;

bool BFSUtil(int s, vector<int> adj[], vector<bool> &visited, int verticiesNum, string wrestlers[]);

// Handles disconnected graphs, runs BFSUtil for all unvisited verticies
bool Bipartite_BFS(vector<int> adj[], int V, string names[])
{
  string wrestlers[V*V];
  
  vector<bool> visited(V, false);
  
  for (int u=0; u<V; u++) {
    if (visited[u] == false) {
      bool runResults = BFSUtil(u, adj, visited, V*V, wrestlers);
      if (runResults == false) {
	cout << "No, Impossible" << endl;
	return false;
      }
    }
  }

  cout << "Yes" << endl << "Babyfaces: ";

  // Convert the wrestler integer indexes to their corresponding names
  for(int i = 0; i < V*V; i++) {
    if(wrestlers[i] == "Babyface")
      cout << names[i] << " ";
  }
  
  cout << endl << "Heels: ";
  
  for(int i = 0; i < V*V; i++) {
    if(wrestlers[i] == "Heel")
      cout << names[i] << " ";
  }

  cout << endl;
  
  return true;
}

// -1 = white, 0 = gray, 1 = black
bool BFSUtil(int s, vector<int> adj[], vector<bool> &visited, int verticiesNum, string wrestlers[])
{
  int color[verticiesNum];

  // Initialize all colors to white (-1)
  for(int i=0; i < verticiesNum; i++)
    color[i] = -1;

  // Ititialize first wrestler to Babyface
  // And color to gray (0)
  wrestlers[s] = "Babyface";
  color[s] = 0; 

  queue<int> Q;
  
  //  cout << "Initial Push " << s << endl;
  // Add initial vertex
  Q.push(s);

  while(!Q.empty())
    {
      // u is the vertex in the front of the queue
      int u = Q.front();
      Q.pop();
      
      // Iterate through the u's adj list of the ith vertex
      for(int i = 1; i < adj[u].size(); ++i)
	{
	  // Set v to element i of adjacent verticies to adj[s]
	  int v = adj[u][i];
	  	  
	  // IF a discovered (gray) node and its adjacent have same color not bipartite
	  if(color[v] == 0 && wrestlers[v] == wrestlers[u]) {
	    return false;
	  }
	  // Else if node is undiscovered
	  else if(color[v] == -1)
	    {
	      // Set it to discovered, 0 (gray)
	      color[v] = 0;
	      visited[v] = true;
	      Q.push(v);
	    }
	  
	  if (wrestlers[u] == "Babyface")
	    wrestlers[v] = "Heel";
	  else
	    wrestlers[v] = "Babyface";
	}
      
      // Set node to processed, 1 (black)
      color[u] = 1;
    }
  
  return true;
}

// A utility function to print the adjacency list
// representation of graph
void printGraph(vector<int> adj[], int V)
{
    for (int v = 0; v < V; ++v)
    {
        cout << "\n Adjacency list of vertex "
             << v << "\n head ";
        for (auto x : adj[v])
           cout << "-> " << x;
        printf("\n");
    }
}

// Mainly contains file I/O
int main(int argc, char *argv[])
{
  if ( argc != 2)
    cout << "usage: " << argv[0] << " <filename>" << endl;
  
  ifstream inputFile;
  ofstream outputFile;
  
  string line; // Temporary variable for reading in lines
  int wrestlersNum, rivalriesNum; // The number of wrestlers in a given set

  inputFile.open(argv[1]);
  
  if (!inputFile || !outputFile) {
    cout << "Error! Unable to open file.";
    exit(1);
  }

  // Get the string of the first value, the number of wrestlers in the set
  getline(inputFile, line);
  
  // Process the line string as a stream
  stringstream lineStream(line);
  string currentVal;
  
  // # of wrestlers in the set
  lineStream >> currentVal;
  
  wrestlersNum = stoi(currentVal); // Convert to number
  
  // Create the adjacency list of size # of wrestlers
  // And keep track of the names
  vector<int> adj[wrestlersNum];
  string names[wrestlersNum];
  int length = wrestlersNum;
  
  int i = 0;
  
  // Add the wrestlers to the adjacency list
  while (wrestlersNum != 0) {
    // Get the next line
    lineStream.clear();
    
    getline(inputFile, line);
    lineStream.str(line);
    
    // While still reading from the line stream
    // Continue reading string
    lineStream >> currentVal; // wrestler name

    adj[i].push_back(i); // Add number that corresponds with wrestler
    names[i] = currentVal; // Keep track of name of wrestler
    
    wrestlersNum--;
    i++;
  }
  
  // Add the edges that represent the rivalries
  // Get the next line
  lineStream.clear();
  
  getline(inputFile, line);
  lineStream.str(line);
  
  // While still reading from the line stream
  // Continue reading string
  lineStream >> currentVal; // # of rivalries
  
  rivalriesNum = stoi(currentVal); // Convert to number
    
  i = 0;
    
  string currentVal2;
  int wrestler1;
  int wrestler2;
  
  while (rivalriesNum != 0) {
    // Get the next line
    lineStream.clear();
    
    getline(inputFile, line);
    lineStream.str(line);
      
    lineStream >> currentVal; // wrestler name
    lineStream >> currentVal2; // second wrestler's name

    // Get integer indexes that correspond to wrestlers
    for (int j = 0; j < length; j++) {
      if (names[j] == currentVal) {
	wrestler1 = j;
      }
      if (names[j] == currentVal2) {
	wrestler2 = j;
      }
    }
      
    // Add the edge of the rivalry to the appropriate wrestler
    adj[wrestler1].push_back(wrestler2);
    adj[wrestler2].push_back(wrestler1);
    
    rivalriesNum--;
    i++;
  }

  // printGraph(adj, length);
  
  // Determine whether the graph is bipartite
  Bipartite_BFS(adj, length, names);

  inputFile.close();

  return 0;
}
