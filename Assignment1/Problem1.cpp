#include <iostream>
#include <fstream>
#include <string>
using namespace std;
int insertIntoSortedArray(int myArray[], int numEntries, int newValue)
{
  int z = numEntries;
  int myArr[100];
  for (int i = 0; i < 100; i++)
  {
    myArr[i] = myArray[i];
  }
  if (numEntries == 0)
  {
    myArray[0] = newValue;
    cout << myArray[0] << endl;
    return z + 1;
  }
  else
  {
    for (int i = 0; i <= numEntries; i++)
    {
      if (myArray[i] > newValue)
      {
        for (int n = i + 1; n < numEntries + 1; n++)
        {
          myArray[n] = myArr[n - 1];
        }
        myArray[i] = newValue;
        break;
      }
      else if (i == numEntries)
      {
        myArray[i] = newValue;
      }
    }
    for (int i = 0; i < numEntries; i++)
    {
      cout << myArray[i] << ",";
    }
    cout << myArray[numEntries] << endl;
  }
  return z + 1;
}
int main(int argc, const char *argv[])
{
  ifstream file;
  int numArray[100];
  file.open(argv[1]);
  if (file.fail())
  {
    cout << "Failed to open the file." << endl;
  }
  else
  {
    string num;
    for (int i = 0; i < 100; i++)
    {
      getline(file, num);
      if (!file.fail())
      {
        insertIntoSortedArray(numArray, i, stoi(num));
      }
    }
  }
}
