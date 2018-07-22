//Pearce.h and  file
#ifndef pearce_h
#define pearce_h

#define UNVISITED -1 //Boost graph library starts indexing the vertices from 0, so we use -1.

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/adjacency_iterator.hpp>
#include <stack>

using namespace boost;

/* Definintion of the struct property for the vertices */
struct VertexPearceProperty {
  int rindex = UNVISITED;
};

// Definition of a directed graph with the VertexProperty specified above.
typedef boost::adjacency_list<listS, vecS, directedS, VertexPearceProperty> pearceGraph;


//The actual function used to call the two above.
std::vector<std::vector<int> > pearce(pearceGraph &graph);
pearceGraph createPearceGraph();
void pearceStrongConnect (pearceGraph::adjacency_iterator vertexIt, int &number);
void pearceStrongConnect (pearceGraph::vertex_iterator vertexIt, int &number);


#endif
