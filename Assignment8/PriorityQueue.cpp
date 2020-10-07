#include <iostream>
#include <string>
#include "PriorityQueue.hpp"
using namespace std;

void swap(GroupNode *a, GroupNode *b)
{
  GroupNode temp = *a;
  *a = *b;
  *b = temp;
}

//Purpose: maintain heap properties by swapping node with parent if necessary
//swap if node has higher priority than parent
void PriorityQueue::repairUpward(int nodeIndex)
{
  if (priorityQueue[nodeIndex].groupSize > priorityQueue[((nodeIndex-1)/2)].groupSize) //correct priority
  {
    return;
  }
  else if(priorityQueue[nodeIndex].groupSize < priorityQueue[((nodeIndex-1)/2)].groupSize) //node has higher priority, swap
  {
    swap(priorityQueue[nodeIndex], priorityQueue[((nodeIndex-1)/2)]);
    repairUpward((nodeIndex-1)/2);
  }
  else //group size is the same
  {
    if(priorityQueue[nodeIndex].cookingTime > priorityQueue[((nodeIndex-1)/2)].cookingTime) //correct priority
    {
      return;
    }
    else if (priorityQueue[nodeIndex].cookingTime < priorityQueue[((nodeIndex-1)/2)].cookingTime)
    {
      swap(priorityQueue[nodeIndex], priorityQueue[((nodeIndex-1)/2)]);
      repairUpward((nodeIndex-1)/2);
    }
  }
}

// Purpose: maintain heap properties by swapping node with child if necessary
//swap with highest priority child if node has lower priority than one or both children
void PriorityQueue::repairDownward(int nodeIndex)
{
  int leftChild = ((2*nodeIndex) + 1);
  int rightChild = ((2*nodeIndex) + 2);
  int highestPriorityChild;
  if(nodeIndex >= currentQueueSize || leftChild >= currentQueueSize)
  {
    return;
  }
  highestPriorityChild = leftChild;
  if(rightChild < currentQueueSize)
  {
    if(priorityQueue[rightChild].groupSize < priorityQueue[highestPriorityChild].groupSize)
    {
      highestPriorityChild = rightChild;
    }
    else if (priorityQueue[rightChild].groupSize == priorityQueue[highestPriorityChild].groupSize && priorityQueue[rightChild].cookingTime < priorityQueue[highestPriorityChild].cookingTime)
    {
      highestPriorityChild = rightChild;
    }
  }
  cout << "n " << nodeIndex << " " << priorityQueue[nodeIndex].groupName << " "<< priorityQueue[nodeIndex].groupSize << " " << priorityQueue[nodeIndex].cookingTime << endl;
  cout << "h " << highestPriorityChild << " " << priorityQueue[highestPriorityChild].groupName << " " << priorityQueue[highestPriorityChild].groupSize << " " << priorityQueue[highestPriorityChild].cookingTime << endl;
  if (priorityQueue[nodeIndex].groupSize < priorityQueue[highestPriorityChild].groupSize) //correct priority
  {
    return;
  }
  else if(priorityQueue[nodeIndex].groupSize > priorityQueue[highestPriorityChild].groupSize) //node has lower priority, swap
  {
    swap(priorityQueue[nodeIndex], priorityQueue[highestPriorityChild]);
    repairDownward(highestPriorityChild);
  }
  else //group size is the same
  {
    if(priorityQueue[nodeIndex].cookingTime < priorityQueue[highestPriorityChild].cookingTime) //correct priority
    {
      return;
    }
    else
    {
      swap(priorityQueue[nodeIndex], priorityQueue[highestPriorityChild]);
      repairDownward(highestPriorityChild);
    }
  }
}

//Purpose: perform all operations necessary to instantiate a class object
PriorityQueue::PriorityQueue(int queueSize)
{
  maxQueueSize = queueSize;
  currentQueueSize = 0;
  priorityQueue = new GroupNode[queueSize];
}

// Purpose: free all resources that the object has acquired
PriorityQueue::~PriorityQueue()
{
  delete [] priorityQueue;
}

// Purpose: enqueue new group into priority queue; call other
void PriorityQueue::enqueue (std::string _groupName, int _groupSize, int _cookingTime)
{
  if(currentQueueSize == maxQueueSize)
  {
    cout << "Heap full, cannot enqueue" << endl;
    return;
  }
  GroupNode n;
  n.groupName = _groupName;
  n.groupSize = _groupSize;
  n.cookingTime = _cookingTime;
  priorityQueue[currentQueueSize] = n;
  repairUpward(currentQueueSize);
  currentQueueSize++;
}

//Purpose: remove the group (allocate the table) at the front of the priority queue from
void PriorityQueue::dequeue()
{
  if(currentQueueSize <= 0)
  {
    cout << "Heap empty, cannot dequeue" << endl;
    return;
  }
  else if(currentQueueSize == 1)
  {
    currentQueueSize--;
    return;
  }
  else
  {
    priorityQueue[0] = priorityQueue[currentQueueSize - 1];
    currentQueueSize--;
    repairDownward(0);
  }
}

// return: groupID of the group at the front of the priority queue
GroupNode PriorityQueue::peek()
{
  if(currentQueueSize == 0)
  {
    cout << "Heap empty, nothing to peek" << endl;
    GroupNode n;
    return n;
  }
  else
  {
    return priorityQueue[0];
  }
}

//return: true if queue is full, false otherwise
bool PriorityQueue::isFull()
{
  if(currentQueueSize == maxQueueSize)
  {
    return true;
  }
  return false;
}

// return: true if queue is empty, false otherwise
bool PriorityQueue::isEmpty()
{
  if(currentQueueSize == 0)
  {
    return true;
  }
  return false;
}
