#include "ProducerConsumer.hpp"
#include <iostream>
#include <string>
using namespace std;

int size = 0;

ProducerConsumer::ProducerConsumer()
{
  queueFront = -1;
  queueEnd = -1;
}

bool ProducerConsumer::isEmpty()
{
  if(size == 0)
  {
    return true;
  }
  return false;
}

bool ProducerConsumer::isFull()
{
  if(queueSize() == 20)
  {
    return true;
  }
  return false;
}

void ProducerConsumer::enqueue(string player) //circular
{
  if(!isFull())
  {
    if(isEmpty())
    {
      size++;
      queueFront++;
      queueEnd++;
      queue[queueFront] = player;
    }
    else
    {
      size++;
      queueEnd++;
      queue[queueEnd] = player;
    }
  }
  else
  {
    cout << "Queue full, cannot add new item" << endl;
  }
}

void ProducerConsumer::dequeue() // circular
{
  if(!isEmpty())
  {
    size--;
    queueFront++;
  }
  else
  {
    cout << "Queue empty, cannot dequeue an item" << endl;
  }
}

int ProducerConsumer::queueSize()
{
  return size;
}

string ProducerConsumer::peek()
{
  if (isEmpty())
  {
    cout << "Queue empty, cannot peek" << endl;
    return "";
  }
  else
  {
    return queue[queueFront];
  }
}
