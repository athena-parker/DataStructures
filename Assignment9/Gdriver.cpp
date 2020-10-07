#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "Graph.hpp"
using namespace std;

int main(int argc, char const *argv[])
{
  Graph g;
  ifstream file;
  file.open(argv[1]);
  string cities;
  string piece;
  string temparr[100];
  string citiesarr[100];
  int numPieces;
  int getlineCounter = 0;
  while(getline(file, cities))
  {
    numPieces = 0;
    stringstream ss(cities);
    while(getline(ss, piece, ','))
    {
      if(piece!= "")
      {
        temparr[numPieces] = piece;
        numPieces++;
      }
    }
    if(getlineCounter == 0)
    {
      for(int i = 1; i < numPieces; i++)
      {
        citiesarr[i - 1] = temparr[i];
        g.addVertex(temparr[i]);
        cout << temparr[i] << endl;
      }
    }
    else if (getlineCounter > 0)
    {
      for(int i = 1; i < numPieces; i++)
      {
        if(stoi(temparr[i]) > 0)
        {
          cout << " ... Reading in " << temparr[0] << " -- " << citiesarr[i-1] << " -- " << temparr[i] << endl;
          g.addEdge(temparr[0], citiesarr[i-1], stoi(temparr[i]));
        }
      }
    }
    getlineCounter++;
  }
  cout << "------------------------------" << endl;
  cout << "Breadth First Traversal" << endl;
  cout << "------------------------------" << endl;
  g.printBFT();
  cout << "------------------------------" << endl;
  cout << "Depth First Traversal" << endl;
  cout << "------------------------------" << endl;
  g.printDFT();
  cout << "------------------------------" << endl;
  cout << "Display Edges" << endl;
  cout << "------------------------------" << endl;
  g.displayEdges();
  return 0;
}
