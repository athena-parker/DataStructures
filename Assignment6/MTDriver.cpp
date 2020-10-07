#include "MovieTree.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;


void menu()
{
	cout << "======Main Menu======" << endl;
	cout << "1. Print the inventory" << endl;
	cout << "2. Delete a movie" << endl;
  cout << "3. Quit" << endl;
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
  string title;
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
    tree.addMovie(stoi(treetemp[0]), treetemp[1], stoi(treetemp[2]), stof(treetemp[3]));
		//something wrong in here
  }
	string choice;
  string nut;
	while (choice != "3")
	{
		 menu();
		 getline(cin, choice);
		 switch (stoi(choice))
		 {
			 case 1:
					 tree.printMovieInventory();
					 break;

			 case 2:
					 cout << "Enter a movie title:" << endl;
					 getline(cin, title);
					 tree.deleteMovie(title);
					 break;

       case 3:
           cout << "Goodbye!" << endl;
           break;

			 default:
					 cout << "invalid input" << endl;
					 cout << endl;
           break;
		 }
	 }
}
