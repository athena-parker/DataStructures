#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;

struct wordItem
{
  string word;
  int count;
};

void getStopWords(const char *ignoreWordFileName, string ignoreWords[])
{
  ifstream file;
  string line;
  file.open(ignoreWordFileName);
  if (file.fail())
  {
    cout << "Failed to open " << ignoreWordFileName << endl;
  }
  else
  {
    for (int i = 0; i < 50; i++)
    {
      getline(file, line);
      ignoreWords[i] = line;
    }
  }
}

bool isStopWord(string word, string ignoreWords[])
{
  for (int i = 0; i < 50; i++)
  {
    if (ignoreWords[i] == word)
      return true;
  }
  return false;
}

int getTotalNumberNonStopWords(wordItem uniqueWords[], int length)
{
  int numTotal = 0;
  for(int i = 0; i < length; i++)
  {
    numTotal += uniqueWords[i].count;
  }
  return numTotal;
}

void arraySort(wordItem uniqueWords[], int length)
{
  wordItem temp;
  for(int i = 0; i <= length; i++)
  {
    for(int j = 0; j <= length - 1; j++)
    {
      if(uniqueWords[j].count < uniqueWords[j+1].count)
      {
        temp = uniqueWords[j];
        uniqueWords[j] = uniqueWords[j+1];
        uniqueWords[j+1] = temp;
      }
    }
  }
}

void printTopN(wordItem uniqueWords[], int topN, int totalNumWords)
{
  float probability = 0;
  for(int i = 0; i < topN; i++)
  {
    probability = (float) uniqueWords[i].count / totalNumWords;
    cout << fixed << setprecision(4) << probability << " - " << uniqueWords[i].word << endl;
  }
}

int main(int argc, const char *argv[])
{
  if (argc != 4)
  {
    cout << "Usage: Assignment2Solution <number of words> <inputfilename.txt> <ignoreWordsfilename.txt>" << endl;
    return -1;
  }
  wordItem *wordsArr = new wordItem[100];
  int currentArrSize = 0;
  int arrSize = 100;
  string ignoreWords[50];
  int numDoubles = 0;
  ifstream file;
  file.open(argv[2]);
  string word;
  getStopWords(argv[3], ignoreWords);
  while(getline(file, word, ' '))
  {
    if(currentArrSize == arrSize)
    {
      wordItem *waP = new wordItem[arrSize * 2];
      for (int n = 0; n < arrSize; n++)
      {
        waP[n] = wordsArr[n];
      }
      delete[] wordsArr;
      wordsArr = waP;
      numDoubles++;
      arrSize = 2 * arrSize;
    }
    if(currentArrSize == 0)
    {
      wordsArr[0].word = word;
      wordsArr[0].count = 1;
      currentArrSize++;
    }
    else if(!isStopWord(word, ignoreWords))
    {
      bool flag = false;
      for(int z = 0; z < currentArrSize; z++)
      {
        if (wordsArr[z].word == word)
        {
          wordsArr[z].count++;
          flag = true;
          break;
        }
      }
      if (flag == false)
      {
        wordsArr[currentArrSize].word = word;
        wordsArr[currentArrSize].count = 1;
        currentArrSize++;
      }
    }
  }
  int totalWords = getTotalNumberNonStopWords(wordsArr, currentArrSize);
  cout << "Array doubled: " << numDoubles << endl << "#" << endl;
  cout << "Unique non-common words: " << currentArrSize << endl << "#" << endl;
  cout << "Total non-common words: " << totalWords << endl << "#" << endl;
  arraySort(wordsArr, currentArrSize);
  cout << "Probabilities of top " << argv[1] << " most frequent words" << endl;
  cout << "---------------------------------------" << endl;
  printTopN(wordsArr, stoi(argv[1]), totalWords);
  return 0;
}
