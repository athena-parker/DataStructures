#include <iostream>
#include <string>
#include <sstream>
#include "MovieTree.hpp"
using namespace std;

MovieTree::MovieTree()
{
  root = nullptr;
}

void deleteTree(TreeNode *node)
{
  if(node == nullptr) return;
  if(node->leftChild != nullptr)
  {
    deleteTree(node->leftChild);
  }
  LLMovieNode *temp = node->head;
  while (temp != nullptr)
  {
    LLMovieNode *n = temp;
    node->head = temp->next;
    temp = node->head;
    delete n;
  }
  if(node->rightChild != nullptr)
  {
    deleteTree(node->rightChild);
  }
  node->head = nullptr;
  delete node;
}

MovieTree::~MovieTree()
{
  deleteTree(root);
}

void printMovies(TreeNode *node)
{
  if(node != nullptr)
  {
    if(node->leftChild != nullptr)
    {
      printMovies(node->leftChild);
    }
    cout << "Movies starting with letter: " << node->titleChar << endl;
    LLMovieNode *temp = node->head;
    while (temp != nullptr)
    {
      cout << " >> " << temp->title << " " << temp->rating << endl;
      temp = temp->next;
    }
    if(node->rightChild != nullptr)
    {
      printMovies(node->rightChild);
    }
  }
}

void MovieTree::printMovieInventory()
{
  printMovies(root);
}

TreeNode* addHelper(int ranking, string title, int year, float rating, TreeNode *&node)
{
  LLMovieNode* nn;
  TreeNode *newtn;
  if (node == nullptr)
  {
    nn = new LLMovieNode;
    newtn = new TreeNode;
    nn->title = title;
    nn->ranking = ranking;
    nn->year = year;
    nn->rating = rating;
      newtn->head = nn;
      node = newtn;
      node->titleChar = title[0];
  }
  else
  {
    if(node->titleChar > title[0])
    {
      node->leftChild = addHelper(ranking, title, year, rating, node->leftChild);
    }
    else if(node->titleChar < title[0])
    {
      node->rightChild = addHelper(ranking, title, year, rating, node->rightChild);
    }
    else
    {
    nn = new LLMovieNode;
    nn->title = title;
    nn->ranking = ranking;
    nn->year = year;
    nn->rating = rating;

      LLMovieNode *temp = node->head;
      LLMovieNode *previous = nullptr;
      if(temp->title > nn->title)
      {
        nn->next = node->head;
        node->head = nn;
      }
      else
      {
        while(temp->next != nullptr)
        {
          if(temp->next->title > nn->title)
          {
            previous = temp;
            break;
          }
          temp = temp->next;
        }
        if(previous == nullptr)
        {
          temp->next = nn;
        }
        else
        {
          nn->next = previous->next;
          previous->next = nn;
        }
      }
    }
  }
  return node;
}

void MovieTree::addMovie(int ranking, string title, int year, float rating)
{
  addHelper(ranking, title, year, rating, root);
}

TreeNode* searchTreeNode(TreeNode *root, string title)
{
  while (root != nullptr)
  {
    if(root->titleChar > title[0])
    {
      root = root->leftChild;
    }
    else if (root->titleChar < title[0])
    {
      root = root->rightChild;
    }
    else
    {
      return root;
    }
  }
  return nullptr;
}

LLMovieNode* searchLLNode(LLMovieNode* head, string title)
{
	LLMovieNode* temp = head;
	bool found = false;
	while (!found && temp != nullptr)
	{
		if (temp->title == title)
		{
			found = true;
			return temp;
		}
		temp = temp->next;
	}
	if (found == false)
	{
		return nullptr;
	}
}

TreeNode* getMinValueNode(TreeNode* currNode){

    if(currNode->leftChild == NULL){
      return currNode;
    }
    return getMinValueNode(currNode->leftChild);
}

TreeNode *deleteBSTNode(TreeNode *root, TreeNode *delLetter)
{
  if(root == nullptr)
  {
    return nullptr;
  }
  else if(delLetter->titleChar < root->titleChar)
  {
    root->leftChild = deleteBSTNode(root->leftChild, delLetter);
  }
  else if(delLetter->titleChar > root->titleChar)
  {
    root->rightChild = deleteBSTNode(root->rightChild, delLetter);
  }else{

  if(delLetter->leftChild == nullptr && delLetter->rightChild == nullptr) //no children
  {
    if (delLetter->parent == nullptr) //if it is the root
    {
      delete root;
      root = nullptr;
      return nullptr;
    }
    if (delLetter->titleChar < delLetter->parent->titleChar)
    {
      delLetter->parent->leftChild = nullptr;
    }
    else
    {
      delLetter->parent->rightChild = nullptr;
    }
    delete delLetter;
    return root;
  }
  else if(delLetter->leftChild == nullptr) //only right child
  {
    TreeNode *temp = delLetter->rightChild;
    delete delLetter;
    return temp;
  }
  else if(delLetter->rightChild == nullptr) //only left child
  {
    TreeNode *temp = delLetter->leftChild;
    delete delLetter;
    return temp;
  }
  else //two children
  {
    TreeNode *temp = getMinValueNode(root->rightChild);
    root->titleChar = temp->titleChar;
    root->head=temp->head;
    root->rightChild = deleteBSTNode(root->rightChild, temp);
    return root;
  }
  }
}

void MovieTree::deleteMovie(string title)
{
  TreeNode *toDelLetter;
  LLMovieNode *toDel;
  LLMovieNode *ntemp;
  TreeNode *rnode;
  if(root == nullptr)//if tree empty
  {
    cout << "Movie: " << title << " not found, cannot delete." << endl;
    return;
  }
  else
  {
    rnode = root;
    //toDelLetter = new TreeNode;
    toDelLetter = searchTreeNode(rnode, title);
    if(toDelLetter == nullptr) //if letter node empty
    {
      cout << "Movie: " << title << " not found, cannot delete." << endl;
    }
    else
    {
      //toDel = new LLMovieNode;
      toDel = searchLLNode(toDelLetter->head, title);
      if(toDelLetter->head == toDel) //node to delete is first in list
      {
        if(toDelLetter->head->next != nullptr) //if it is not the only node
        {
          toDelLetter->head = toDelLetter->head->next;
          delete toDel;
        }
        else //if it is the only node
        {
          delete toDel;
          // toDelLetter = new TreeNode;
          // toDelLetter = searchTreeNode(rnode, title);
          root=deleteBSTNode(root, toDelLetter);
        }
      }
      else //node to delete is not first
      {
        bool flag = 0;
        ntemp = toDelLetter->head;
        while (!flag)
        {
          if (ntemp->next == toDel)
          {
            ntemp->next = toDel->next;
            delete toDel;
            flag = 1;
          }
          else
          {
            ntemp = ntemp->next;
          }
        }
      }
    }
  }
}
