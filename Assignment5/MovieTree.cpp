#include <iostream>
#include <string>
#include "MovieTree.hpp"
using namespace std;

MovieTree::MovieTree()
{
  root = nullptr;
}

void deleteTree(MovieNode *node)
{
    if(node->leftChild != nullptr)
    {
      deleteTree(node->leftChild);
    }
    if(node->rightChild != nullptr)
    {
      deleteTree(node->rightChild);
    }
      delete node;
}

MovieTree::~MovieTree()
{
  deleteTree(root);
}

MovieNode* MovieTree::search(string title) //works
{
  MovieNode* node = new MovieNode;
  node = root;
  while (node != nullptr)
  {
    if(node->title > title)
    {
      node = node->leftChild;
    }
    else if (node->title < title)
    {
      node = node->rightChild;
    }
    else
    {
      return node;
    }
  }
  return nullptr;
}

void printMovies(MovieNode *node)
{
  if(node != nullptr)
  {
    if(node->leftChild != nullptr)
    {
      printMovies(node->leftChild);
    }
    cout << "Movie: " << node->title << " " << node->rating << endl;
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

MovieNode* addHelper(int ranking, string title, int year, float rating, MovieNode *&node)
{
  MovieNode* nn = new MovieNode;
  nn->title = title;
  nn->ranking = ranking;
  nn->year = year;
  nn->rating = rating;
  if (node == nullptr)
  {
      node = nn;
  }
  else
  {
    if(node->title > title)
    {
      node->leftChild = addHelper(ranking, title, year, rating, node->leftChild);
    }
    else
    {
      node->rightChild = addHelper(ranking, title, year, rating, node->rightChild);
    }
  }
  return node;
}

void MovieTree::addMovieNode(int ranking, string title, int year, float rating)
{
  addHelper(ranking, title, year, rating, root);
}

void MovieTree::findMovie(string title) //works
{
  MovieNode* node = new MovieNode;
  node = search(title);
  if(node == nullptr)
  {
    cout << "Movie not found." << endl;
  }
  else
  {
    cout << "Movie Info:" << endl;
    cout << "==================" << endl;
    cout << "Ranking:" << node->ranking << endl;
    cout << "Title  :" << node->title << endl;
    cout << "Year   :" << node->year << endl;
    cout << "rating :" << node->rating << endl;
  }
}

void printQuery(MovieNode *node, float rating, int year) //working
{
  if(node != nullptr)
  {
    if(node->rating >= rating && node->year >= year)
    {
      cout << node->title << "(" << node->year << ") " << node->rating << endl;
    }
    if(node->leftChild != nullptr)
    {
      printQuery(node->leftChild, rating, year);
    }
    if(node->rightChild != nullptr)
    {
      printQuery(node->rightChild, rating, year);
    }
  }
}

void MovieTree::queryMovies(float rating, int year) //working
{
  cout << "Movies that came out after " << year << " with rating at least " << rating << ":" << endl;
  printQuery(root, rating, year);
}

void sumNodes(MovieNode* node, float &sum, int &count) //working
{
  count++;
  sum += node->rating;
  if (node != nullptr)
  {
    if(node->leftChild != nullptr)
    {
      sumNodes(node->leftChild, sum, count);
    }
    if(node->rightChild != nullptr)
    {
      sumNodes(node->rightChild, sum, count);
    }
  }
}

void MovieTree::averageRating() //working
{
  float sum = 0;
  int count = 0;
  if(root == nullptr)
  {
    cout << "Average rating:0" << endl;
  }
  else
  {
    sumNodes(root, sum, count);
    cout << "Average rating:" << sum/count << endl;
  }
}
