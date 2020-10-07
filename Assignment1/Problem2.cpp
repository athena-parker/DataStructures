#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

struct User
{
  string username;
  float gpa;
  int age;
};

int split(string toSplit, char delimiter, string splitted[], int size)
{
    int pieces = 0;
    stringstream ss(toSplit); //creates stream variable
    string word;
    while(getline(ss, word, delimiter)) //gets lines delimited by delimiter
    {
        if (word != "")
        {
            splitted[pieces] = word; //stores into array
            pieces++;
        }
    }
    return pieces;
}

void split(string toSplit, string splitted[])
{
  int p = 0;
  for(int i = 0; i < toSplit.length(); i++)
  {
    if(toSplit[i] == ',')
    {
      splitted[p] = toSplit.substr(0, i);
      toSplit = toSplit - toSplit.substr(0, i);
      p++;
    }
  }
}

void addUser(User users[], string username, float gpa, int age, int length)
{
  for (int i = 0; i < length; i++)
  {
    if (users[i].username == "")
    {
      users[i].username = username;
      users[i].gpa = gpa;
      users[i].age = age;
      break;
    }
  }
}

void printList(const User users[], int length)
{
  for (int i = 0; i < length; i++)
  {
    cout << users[i].username << " [" << users[i].gpa << "] age: " << users[i].age << endl;
  }
}

int main(int argc, const char *argv[])
{
  ifstream infile;
  ofstream outfile;
  string tempArray[15];
  string piecesArray[3];
  struct User userArray[15];
  string line;
  infile.open(argv[1]);
  outfile.open(argv[2]);
  int numbo = 0;
  for (int i = 0; i < 15; i++)
  {
    while (getline(infile, line))
    {
      if (!infile.fail())
      {
        numbo++;
        tempArray[i] = line;
        split(tempArray[i], ',', piecesArray, 3);
        addUser(userArray, piecesArray[0], stof(piecesArray[1]), stoi(piecesArray[2]), numbo);
        if(stof(piecesArray[1]) >= stof(argv[3]))
        {
          outfile << tempArray[i] << endl;
        }
      }
    }
  }
  printList(userArray, numbo);
}
