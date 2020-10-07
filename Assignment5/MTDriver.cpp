#include "MovieTree.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;


void menu()
{
	cout << "======Main Menu======" << endl;
  cout << "1. Find a movie" << endl;
	cout << "2. Query movies" << endl;
	cout << "3. Print the inventory" << endl;
	cout << "4. Average Rating of movies" << endl;
  cout << "5. Quit" << endl;
}

int main(int argc, char const *argv[])
{
  string treetemp[4];
	MovieTree tree;
  ifstream file;
  string movie;
  string bit;
  int numPieces = 0;
  string piece;
  string minrating;
  string minyear;
  file.open(argv[1]);
  while(getline(file, movie))
  {
    numPieces = 0;
    stringstream ss(movie);
    while(getline(ss, piece, ','))
    {
      if(piece!= "")
      {
        treetemp[numPieces] = piece;
        numPieces++;
      }
    }
    tree.addMovieNode(stoi(treetemp[0]), treetemp[1], stoi(treetemp[2]), stof(treetemp[3]));
  }
	string choice;
  string nut;
	while (choice != "5")
	{
		 menu();
		 getline(cin, choice);
		 switch (stoi(choice))
		 {
			 case 1:
					 cout << "Enter title:" << endl;
					 getline(cin, bit);
					 tree.findMovie(bit);
					 break;

			 case 2:
					 cout << "Enter minimum rating:" << endl;
					 getline(cin, minrating);
           cout << "Enter minimum year:" << endl;
           getline(cin, minyear);
					 tree.queryMovies(stoi(minrating), stoi(minyear));
					 break;

			 case 3:
					 tree.printMovieInventory();
					 break;

       case 4:
           tree.averageRating();
           break;

       case 5:
           cout << "Goodbye!" << endl;
           break;

			 default:
					 cout << "invalid input" << endl;
					 cout << endl;
           break;
		 }
	 }
}
