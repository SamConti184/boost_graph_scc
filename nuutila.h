//Nuutila.h and  file
#ifndef nuutila_h
#define nuutila_h

#define UNVISITED -1 //Boost graph library starts indexing the vertices from 0, so we use -1.

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/adjacency_iterator.hpp>
#include <stack>

using namespace boost;

/* Definintion of the struct property for the vertices */
struct VertexNuutilaProperty {
  int root;
  int number = UNVISITED;
  bool inComponent = false;
};

// Definition of a directed graph with the VertexProperty specified above.
typedef boost::adjacency_list<listS, vecS, directedS, VertexNuutilaProperty> nuutilaGraph;


//The actual function used to call the two above.
std::vector<std::vector<int> >  nuutila1(nuutilaGraph &graph);
nuutilaGraph createNuutilaGraph();
void nuutilaStrongConnect (nuutilaGraph::vertex_iterator vertexIt, int &number);
void nuutilaStrongConnect (nuutilaGraph::adjacency_iterator vertexIt, int &number);


#endif
