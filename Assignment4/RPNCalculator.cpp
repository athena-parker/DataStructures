#include <iostream>
#include <string>
#include "RPNCalculator.hpp"
using namespace std;

RPNCalculator::RPNCalculator()
{
  stackHead = NULL;
}

RPNCalculator::~RPNCalculator()
{
  while (stackHead != NULL)
  {
    pop();
  }
  stackHead = NULL;
}

bool RPNCalculator::isEmpty()
{
  if(stackHead == NULL)
  {
    return true;
  }
  else
  {
    return false;
  }
}

void RPNCalculator::push(float num)
{
  Operand* nn = new Operand;
  nn->number = num;
  if (stackHead == NULL)
  {
    stackHead = nn;
    nn->next = NULL;
  }
  else
  {
    nn->next = stackHead;
    stackHead = nn;
  }
}

void RPNCalculator::pop()
{
  if (isEmpty())
  {
    cout << "Stack empty, cannot pop an item." << endl;
  }
  else
  {
    Operand* temp = stackHead;
    stackHead = stackHead->next;
    delete temp;
  }
}

Operand* RPNCalculator::peek()
{
  if(!isEmpty())
    return stackHead;
  else
  {
    cout << "Stack empty, cannot peek." << endl;
    return NULL;
  }
}

bool RPNCalculator::compute(string symbol)
{
  if(isEmpty())
  {
    cout << "err: not enough operands" << endl;
    return false;
  }
  float one = stackHead->number;
  float two = 0;
  pop();
  if(isEmpty())
  {
    cout << "err: not enough operands" << endl;
    push(one);
    return false;
  }
  else
  {
    two = stackHead->number;
    pop();
  }
  if(symbol == "+")
  {
    float newnum = one + two;
    push(newnum);
    return true;
  }
  else if (symbol == "*")
  {
    float newnum = one * two;
    push(newnum);
    return true;
  }
  else // check this first
  {
    cout << "err: invalid operation" << endl;
    return false;
  }
}
