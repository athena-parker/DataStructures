#include <iostream>
#include <string>
#include <iomanip>
#include "HashTable.hpp"
using namespace std;

HashTable::HashTable(int hashTableSize)
{
  this->hashTableSize = hashTableSize;
  numCollisions = 0;
  numItems = 0;
  hashTable = new wordItem*[hashTableSize];
  for (int i = 0; i < hashTableSize; i++)
  {
    hashTable[i] = nullptr;
  }
}

HashTable::~HashTable()
{
  wordItem *temp;
  wordItem *n;
  for(int i = 0; i < hashTableSize; i++)
  {
    if(hashTable[i] != nullptr)
    {
      if (hashTable[i]->next != nullptr)
      {
        temp = hashTable[i];
        while(temp != nullptr)
        {
          hashTable[i] = temp->next;
          n = temp;
          delete n;
          temp = hashTable[i];
        }
      }
    }
  }
}

unsigned int HashTable::getHash(string word)
{
  unsigned int hashValue = 5381;
  int length = word.length();
  for (int i = 0; i < length; i++)
  {
    hashValue = ((hashValue<<5)+hashValue) + word[i];
  }
  hashValue %= hashTableSize;
  return hashValue;
}

wordItem* HashTable::searchTable(string word)
{
  int index = getHash(word);
  if(hashTable[index] != nullptr)
  {
    if(hashTable[index]->word == word)
       return hashTable[index];
    wordItem* temp = hashTable[index];
    while(temp != nullptr) //search linked list for node
    {
      if (temp->word == word)
      {
        return temp;
      }
      temp = temp->next;
    }
  }
  return nullptr;
}

wordItem* createNode(string word, wordItem* next) //working
{
  wordItem* nw = new wordItem;
  nw->word = word;
  nw->next = next;
  return nw;
}

void HashTable::addWord(string word) //working
{
  numItems++;
  int index = getHash(word);
  if(hashTable[index] == nullptr) //if index is empty
  {
    hashTable[index] = createNode(word, nullptr);
  }
  else //if need to add to linked list
  {
    wordItem *n = createNode(word, hashTable[index]);
    hashTable[index] = n;
    numCollisions++;
  }
}

bool HashTable::isInTable(string word)
{
  wordItem *n = searchTable(word);
  if(n != nullptr)
    return true;
  else
    return false;
}

void HashTable::incrementCount(string word)
{
  wordItem *n = searchTable(word);
  if(n != nullptr)
  {
    n->count++;
  }
}

void arraySort(wordItem *uniqueWords[], int length)
{
  wordItem *temp;
  for(int i = 0; i < length; i++)
  {
    for(int j = 0; j < length - 1; j++)
    {
      if(uniqueWords[j]->count < uniqueWords[j+1]->count)
      {
        temp = uniqueWords[j];
        uniqueWords[j] = uniqueWords[j+1];
        uniqueWords[j+1] = temp;
      }
    }
  }
}

void HashTable::printTopN(int n)
{
  int arrIndex = 0;
  wordItem *arr[getTotalNumWords() + 500000];
  wordItem *temp;
  float probability = 0;
  for(int i = 0; i < hashTableSize; i++)
  {
    if(hashTable[i] != nullptr)
    {
      temp = hashTable[i];
      while(temp != nullptr)
      {
        arr[arrIndex] = temp;
        arrIndex++;
        temp = temp->next;
      }
    }
  }
  arraySort(arr, arrIndex);
  for(int j = 0; j < n; j++)
  {
    probability = (float) arr[j]->count/getTotalNumWords();
    cout << fixed << setprecision(4) << probability << " - " << arr[j]->word << endl;
  }
}

int HashTable::getNumCollisions()
{
  return numCollisions;
}

int HashTable::getNumItems()
{
  return numItems;
}

int HashTable::getTotalNumWords() //working
{
  int total = 0;
  wordItem *temp;
  for(int i = 0; i < hashTableSize; i++)
  {
    if(hashTable[i] != nullptr)
    {
      total += hashTable[i]->count;
      if(hashTable[i]->next != nullptr)
      {
        temp = hashTable[i]->next;
        while(temp != nullptr)
        {
          total += temp->count;
          temp = temp->next;
        }
      }
    }
  }
  return total;
}
