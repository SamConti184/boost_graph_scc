//Tarjan.h and  file
#ifndef tarjan_h
#define tarjan_h

#define UNVISITED -1 //Boost graph library starts indexing the vertices from 0, so we use -1.

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/adjacency_iterator.hpp>
#include <stack>

using namespace boost;

/* Definintion of the struct property for the vertices, following Tarjan's indications. */
struct VertexTarjanProperty {
  int lowLink;
  int number = UNVISITED; //vertex initialized as univisited.
  bool onStack;
};

// Definition of a directed graph with the VertexProperty specified above.
typedef boost::adjacency_list<listS, vecS, directedS, VertexTarjanProperty> directGraph;


//The actual function used to call the two above.
std::vector<std::vector<int> > tarjan(directGraph &graph);
int tarjanTest();
void test();
directGraph createGraph();

#endif
