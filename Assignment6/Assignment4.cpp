#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include "MovieTree.hpp"
using namespace std;

int main(int charc, char* argv[])
{
	MovieTree object;
	string user_input, user_movie, rent_movie, delete_movie, line, tempRank, tempTitle, tempYear, tempQuantity;
	ifstream in;

	in.open(argv[1]);
	if (in.fail())
	{
		cout << "File has failed to open.\n";
		return 0;
	}
	while (getline(in, line))
	{
		if (line != "")
		{
			stringstream ss(line);
			cout << "Line: " << line << endl;
			getline(ss, tempRank, ',');
			getline(ss, tempTitle, ',');
			getline(ss, tempYear, ',');
			getline(ss, tempQuantity);
			object.addMovieNode(stoi(tempRank), tempTitle, stoi(tempYear), stoi(tempQuantity));
		}
	}
	in.close();
	while (1)
	{
		cout << "======Main Menu======" << endl; cout << "1. Find a movie" << endl; cout << "2. Rent a movie" << endl;
		cout << "3. Print the inventory" << endl; cout << "4. Delete a movie" << endl; cout << "5. Count the movies" << endl; cout << "6. Quit" << endl;
		getline(cin, user_input);
		if (user_input == "1")
		{
			cout << "Enter title: " << endl;
			getline(cin, user_movie);
			object.findMovie(user_movie);

		}
		else if (user_input == "2")
		{
			cout << "Enter title: " << endl;
			getline(cin, rent_movie);
			object.rentMovie(rent_movie);
		}
			
		else if (user_input == "3")
		{
			object.printMovieInventory();
		}
		else if (user_input == "4")
		{
			cout << "Enter title: " << endl;
			getline(cin, delete_movie);
			object.deleteMovieNode(delete_movie);
		}	
		else if (user_input == "5")
		{
			cout << "Tree contains: \n" <<object.countMovieNodes()<< " movies." << endl;
		}
		else if (user_input == "6")
		{
			cout << "Goodbye!" << endl;
			break;
		}
	}
}
