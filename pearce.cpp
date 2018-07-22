/*
Implementation of the Nuutila algorithm for finding strongly connected components
in a directed graph, as described in the original paper
*/

#include <iostream>
#include <stack>
#include "pearce.h"
using namespace boost;

//Global variables, used to repsect the spatial complexity of the algorithm
std::stack<int> pearceStack; //stack of int, respecting spatial complexity of the paper.
pearceGraph pearGraph;
int c;

//Global variable for keeping the list of strongly connected components.
std::vector<std::vector<int> > pearComponents;


std::vector<std::vector<int> > pearce(pearceGraph &graph){
  pearGraph = graph;
  pearceGraph::vertex_iterator vertexIt, vertexEnd;
  tie(vertexIt, vertexEnd) = vertices(pearGraph); //Returning iterator for vertices.

  int index = 0;
  c = int(num_vertices(pearGraph));

  //Iteration over vertices
  for(; vertexIt != vertexEnd; ++vertexIt) {
    if (pearGraph[*vertexIt].rindex == -1) {
      pearceStrongConnect(vertexIt, index);
    }
  }
  std::vector<std::vector<int> > output = pearComponents;
  pearComponents.clear();
  return output;
}

void pearceStrongConnect (pearceGraph::vertex_iterator vertexIt, int &index){

  bool root = true; //DIFFERENCE: local variable root
  pearGraph[*vertexIt].rindex= index;
  index += 1;

  pearceGraph::adjacency_iterator neighbourIt, neighbourEnd;
  tie(neighbourIt, neighbourEnd) = adjacent_vertices(*vertexIt, pearGraph);
  for(; neighbourIt != neighbourEnd; ++neighbourIt){
    if (pearGraph[*neighbourIt].rindex == -1)
      pearceStrongConnect(neighbourIt, index);
    if (pearGraph[*neighbourIt].rindex < pearGraph[*vertexIt].rindex){
        pearGraph[*vertexIt].rindex = pearGraph[*neighbourIt].rindex;
        root = false;
      }
  }
  if (root){
    //We have found the root of the component
    std::vector<int> scc;
    index -= 1;
    pearceGraph::vertex_descriptor topStackVertex;
    scc.insert(scc.begin(), *vertexIt);
    if(!pearceStack.empty()) //DIFFERENCE - here the stack may be empty, since the root is not on it initially
      topStackVertex = pearceStack.top();
    while (!pearceStack.empty() && pearGraph[topStackVertex].rindex >= pearGraph[*vertexIt].rindex){
        pearGraph[topStackVertex].rindex = c;
        scc.insert(scc.begin(), topStackVertex);
        pearceStack.pop();  //Pop the vertex from the stack
        index -= 1;
        if (!pearceStack.empty())
            topStackVertex = pearceStack.top();
      }
    pearGraph[*vertexIt].rindex = c;
    c -= 1;
    //Adding the newly found scc to the list of them
    pearComponents.push_back(scc);
  } else {
    pearceStack.push(*vertexIt); //DIFFERENCE -> we push here on the task, when we know vertex is no root
  }
}

/*
I wasn't able to find a common super-class between adjacency_iterator and
vertex_iterator, so I had to proceed with this not so much elegant solution:
the two functions are the same, only overloaded on the first paramether. */
void pearceStrongConnect (pearceGraph::adjacency_iterator vertexIt, int &index){

  bool root = true; //DIFFERENCE: local variable root
  pearGraph[*vertexIt].rindex= index;
  index += 1;

  pearceGraph::adjacency_iterator neighbourIt, neighbourEnd;
  tie(neighbourIt, neighbourEnd) = adjacent_vertices(*vertexIt, pearGraph);
  for(; neighbourIt != neighbourEnd; ++neighbourIt){
    if (pearGraph[*neighbourIt].rindex == -1)
      pearceStrongConnect(neighbourIt, index);
    if (pearGraph[*neighbourIt].rindex < pearGraph[*vertexIt].rindex){
        pearGraph[*vertexIt].rindex = pearGraph[*neighbourIt].rindex;
        root = false;
      }
  }
  if (root){
    //We have found the root of the component
    std::vector<int> scc;
    index -= 1;
    pearceGraph::vertex_descriptor topStackVertex;
    scc.insert(scc.begin(), *vertexIt);
    if(!pearceStack.empty()) //DIFFERENCE - here the stack may be empty, since the root is not on it initially
      topStackVertex = pearceStack.top();
    while (!pearceStack.empty() && pearGraph[topStackVertex].rindex >= pearGraph[*vertexIt].rindex){
        pearGraph[topStackVertex].rindex = c;
        scc.insert(scc.begin(), topStackVertex);
        pearceStack.pop();  //Pop the vertex from the stack
        index -= 1;
        if (!pearceStack.empty())
            topStackVertex = pearceStack.top();
      }
    pearGraph[*vertexIt].rindex = c;
    c -= 1;
    //Adding the newly found scc to the list of them
    pearComponents.push_back(scc);
  } else {
    pearceStack.push(*vertexIt); //DIFFERENCE -> we push here on the task, when we know vertex is no root
  }
}

/*
Function to generate a sample graph used for immediate testing of the algorithm
*/
pearceGraph createPearceGraph(){
  pearceGraph graph;
  add_edge (0, 1, graph);
  add_edge (1, 2, graph);
  add_edge (2, 0, graph);
  add_edge (3, 1, graph);
  add_edge (3, 2, graph);
  add_edge (3, 4, graph);
  add_edge (4, 3, graph);
  add_edge (4, 5, graph);
  add_edge (5, 2, graph);
  add_edge (5, 6, graph);
  add_edge (6, 5, graph);
  add_edge (7, 4, graph);
  add_edge (7, 6, graph);
  add_edge (7, 7, graph);
  return graph;
}
