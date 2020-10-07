#include <iostream>
#include <string>
#include "HashTable.hpp"
using namespace std;
#include <iomanip>
#include <fstream>

void getStopWords(char *ignoreWordFileName, HashTable &stopWordsTable) //working
{
  ifstream file;
  string line;
  file.open(ignoreWordFileName);
  if (!file.fail())
  {
    for (int i = 0; i < 50; i++)
    {
      getline(file, line);
      stopWordsTable.addWord(line);
    }
  }
}

bool isStopWord(string word, HashTable &stopWordsTable)
{
  if(!stopWordsTable.isInTable(word))
    return false;
  else
    return true;
}



int main(int argc, char *argv[]) //working
{
  HashTable table(stoi(argv[4]));
  HashTable ignoreWords(50);
  ifstream file;
  file.open(argv[2]);
  string word;
  getStopWords(argv[3], ignoreWords); //filling stop word array
  while(file >> word) //filling other array
  {
    if(!isStopWord(word, ignoreWords))
    {
      if(table.isInTable(word))
      {
        table.incrementCount(word);
      }
      else
      {
        table.addWord(word);
      }
    }
  }
  table.printTopN(stoi(argv[1]));
  cout << "#" << endl;
  cout << "Number of collisions: " << table.getNumCollisions() << endl;
  cout << "#" << endl;
  cout << "Unique non-stop words: " << table.getNumItems() << endl;
  cout << "#" << endl;
  cout << "Total non-stop words: " << table.getTotalNumWords() << endl;
  return 0;
}
