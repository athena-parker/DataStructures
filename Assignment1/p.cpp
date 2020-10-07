#include <iostream>
#include <string>
using namespace std;

void split(string toSplit, string splitted[])
{
  int p = 0;
  for(int i = 0; i < toSplit.length(); i++)
  {
    if(toSplit[i] == ',')
    {
      splitted[p] = toSplit.substr(0, i);
      toSplit.erase(0, i+1);
      cout << splitted[p] << endl;
      p++;
      i = 0;
    }
  }
  splitted[p] = toSplit;
  cout << splitted[p] << endl;
}

int main()
{
  string toSplit = "bird,hi,like,cool";
  string splitted[4];
  split(toSplit, splitted);
  return 0;
}
