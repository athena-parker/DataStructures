#include <iostream>
using namespace std;

struct Node {
    int data;
    Node *next;
};

void print(Node *tail)
{
  Node* temp = new Node;
  temp = tail->next;
  while(temp != tail)
  {
    cout << temp->data << " ";
    temp = temp->next;
  }
  cout << tail->data << endl;
}

Node* shift(Node* tail, int n)
{
  int counter = 0;
  Node* temp = new Node;
  temp = tail->next;
  while(temp != tail)
  {
    counter++;
    temp = temp->next;
  }
  counter++;
  temp = tail->next;
  if (n <= counter)
  {
    for (int i = 0; i < counter; i++)
    {
      for(int j = 0; j < n; j++)
      {
        temp = temp->next;
      }
      temp = temp->next;
    }
    tail = temp;
  }
  else
  {
    for (int i = 0; i < counter; i++)
    {
      for(int j = 0; j < n%counter; j++)
      {
        temp = temp->next;
      }
      temp = temp->next;
    }
    tail = temp;
  }
  return tail;
}

Node* insertEnd(Node* tail, int val)
{
  Node* newNode = new Node;
  newNode->data = val;
  newNode->next = tail->next;
  tail->next = newNode;
  tail = newNode;
  return tail;
}

int main()
{
  //first list 7, 4, 6, 2
  Node *n1 = new Node;
  n1->data = 7;
  Node *n2 = new Node;
  n2->data = 4;
  n1->next = n2;
  Node *n3 = new Node;
  n3->data = 6;
  n2->next = n3;
  Node *n4 = new Node;
  n4->data = 2;
  n3->next = n4;
  n4->next = n1;
  cout << "printing original list ";
  print(n4);
  Node *n5 = new Node;
  n5 = insertEnd(n4, 3);
  cout << "printing list after adding new node ";
  print(n5);
  n5 = shift(n5, 1);
  cout << "printing list after shifting one spot ";
  print(n5);
  n5 = shift(n5, 7);
  cout << "printing list after shifting seven spots ";
  print(n5);

  //second list NULL
  Node *nullhead = new Node;
  nullhead->data = 0;
  nullhead->next = NULL;

  //third list 3, 9, 2
  Node *n31 = new Node;
  n31->data = 3;
  Node *n32 = new Node;
  n32->data = 9;
  n31->next = n32;
  Node *n33 = new Node;
  n33->data = 2;
  n32->next = n33;
  n33->next = n31;

  //fourth list 1, 3, 5, 7
  Node *n41 = new Node;
  n41->data = 1;
  Node *n42 = new Node;
  n42->data = 3;
  n41->next = n42;
  Node *n43 = new Node;
  n43->data = 5;
  n42->next = n43;
  Node *n44 = new Node;
  n44->data = 7;
  n43->next = n44;
  n44->next = n41;

}
