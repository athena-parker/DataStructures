#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include "Graph.hpp"
using namespace std;

Graph::Graph()
{

}

Graph::~Graph()
{

}

vertex* Graph::findVertex(string name)
{
  for(int i = 0; i < vertices.size(); i++)
  {
    if(vertices[i].name == name)
    {
      return &vertices[i];
    }
  }
  return nullptr;
}

void Graph::BFT_traversal(vertex *v)
{
  vector<vertex*> queue;
  //mark current node as visited & enqueue
  v->visited = true;
  queue.push_back(v);
  while(!queue.empty())
  {
    //dequeue vertex and print it
    v = queue.front();
    cout << v->name << endl;
    queue.erase(queue.begin());
    //get all adj vertices of dequeued vertex
    //if not been visited, mark as visited & enqueue
    vector<Edge>::iterator i;
    for(i = v->Edges.begin(); i != v->Edges.end(); i++)
    {
      if(!i->v->visited)
      {
        i->v->visited = true;
        queue.push_back(i->v);
      }
    }
  }
}

void Graph::DFT_traversal(vertex *v)
{
  //mark current node as visited & print
  v->visited = true;
  cout << v->name << endl;

  //recur to adj vertices
  vector<Edge>::iterator i;
  for(i = v->Edges.begin(); i < v->Edges.end(); i++)
  {
    if(!i->v->visited)
    {
      DFT_traversal(i->v);
    }
  }
}

void Graph::addVertex(string cityName)
{
  vertex nv;
  nv.name = cityName;
  vertices.push_back(nv);
}

void Graph::addEdge(string city1, string city2, int distance)
{
  Edge ne;
  vertex *ve = findVertex(city2);
  ne.v = ve;
  ne.distance = distance;
  vertex *ov = findVertex(city1);
  if(ov != nullptr)
    ov->Edges.push_back(ne);
}

void Graph::displayEdges()
{
  //loop through all vertices and adjacent vertices
  for(int i = 0; i < vertices.size(); i++)
  {
    cout<<vertices[i].name<<"-->";
    for(int j = 0; j < vertices[i].Edges.size(); j++)
    {
      cout << vertices[i].Edges[j].v->name << " (";
      cout << vertices[i].Edges[j].distance << " miles)";
      if(j + 1 != vertices[i].Edges.size())
      {
        cout << "***";
      }
    }
    cout<<endl;
  }
}

void Graph::printDFT()
{
  setAllVerticesUnvisited();
  for(int i=0; i<vertices.size(); i++)
  {
    if(!vertices[i].visited)
    {
      DFT_traversal(&vertices[i]);
    }
  }
}

void Graph::printBFT()
{
  setAllVerticesUnvisited();
  for(int i=0; i<vertices.size(); i++)
  {
    if(!vertices[i].visited)
    {
      BFT_traversal(&vertices[i]);
    }
  }
}

void Graph::setAllVerticesUnvisited()
{
  for(int i = 0; i < vertices.size(); i++)
  {
    vertices[i].visited = false;
  }
}
