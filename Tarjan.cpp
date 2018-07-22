/*
Implementation of the Tarjan algorithm for finding strongly connected components
in a directed graph, as described in the original paper.
*/

#include <iostream>
#include <stack>
#include "tarjan.h"

using namespace boost;


/*Global variables, used to reflect more the space complexity of the algorithm:
in order to avoid to fill the call-stack with more than 2 words of memory,
as described in the paper, the following global variables are defined.
They will be accesse throughout the execution of the algorithm instead of being
passed as reference in the recursive calls. */
std::stack<int> verticesStack;
directGraph currentGraph;

//Global variable for keeping the list of strongly connected components.
std::vector<std::vector<int> > components;

void strongConnect (directGraph::vertex_iterator vertexIt, int &number);
void strongConnect (directGraph::adjacency_iterator vertexIt, int &number);

std::vector<std::vector<int> > tarjan(directGraph &graph){
  currentGraph = graph;
  directGraph::vertex_iterator vertexIt, vertexEnd;
  tie(vertexIt, vertexEnd) = vertices(currentGraph); //Returning iterator for vertices.

  int number = 0;

  //Iteration over vertices
  for(; vertexIt != vertexEnd; ++vertexIt) {
    if (currentGraph[*vertexIt].number == UNVISITED) {
      strongConnect(vertexIt, number); //Stack-frame composed by two words
    }
  }
  std::vector<std::vector<int> > output = components;
  components.clear();
  return output;
}

void strongConnect (directGraph::vertex_iterator vertexIt, int &number) {
  currentGraph[*vertexIt].number = number;
  currentGraph[*vertexIt].lowLink = number;
  number += 1;
  //Pushing the pointer to the vertex on to the stack
  verticesStack.push(*vertexIt);
  currentGraph[*vertexIt].onStack = true;

  directGraph::adjacency_iterator neighbourIt, neighbourEnd;
  tie(neighbourIt, neighbourEnd) = adjacent_vertices(*vertexIt, currentGraph);
  for(; neighbourIt != neighbourEnd; ++neighbourIt){
    if (currentGraph[*neighbourIt].number == UNVISITED){
      //We found a tree arc, not yet visited
      strongConnect(neighbourIt, number);
      currentGraph[*vertexIt].lowLink = fmin(currentGraph[*vertexIt].lowLink, currentGraph[*neighbourIt].lowLink);
    } else if (currentGraph[*neighbourIt].number < currentGraph[*vertexIt].number){
      //Frond or cross-link found, we need to check if same SCC
      if (currentGraph[*neighbourIt].onStack == true) {
        currentGraph[*vertexIt].lowLink = fmin(currentGraph[*vertexIt].lowLink, currentGraph[*neighbourIt].number);
      }
    }
  }
  if (currentGraph[*vertexIt].lowLink == currentGraph[*vertexIt].number){
    //We have found the root of the component
    std::vector<int> scc;
    directGraph::vertex_descriptor topStackVertex;
    topStackVertex = verticesStack.top();
    while (!verticesStack.empty() && currentGraph[topStackVertex].number >= currentGraph[*vertexIt].number){
        scc.insert(scc.begin(), topStackVertex);
        currentGraph[topStackVertex].onStack = false;
        verticesStack.pop();
        if (!verticesStack.empty())
          topStackVertex = verticesStack.top();
      }
    //Adding the newly found scc to the list of them
    components.push_back(scc);
  }
}

/*
I wasn't able to find a common super-class between adjacency_iterator and
vertex_iterator, so I had to proceed with this not so much elegant solution:
the two functions are the same, only overloaded on the first paramether. */
void strongConnect (directGraph::adjacency_iterator vertexIt, int &number){
  currentGraph[*vertexIt].number = number;
  currentGraph[*vertexIt].lowLink = number;
  number += 1;
  //Pushing the pointer to the vertex on to the stack
  verticesStack.push(*vertexIt);
  currentGraph[*vertexIt].onStack = true;

  directGraph::adjacency_iterator neighbourIt, neighbourEnd;
  tie(neighbourIt, neighbourEnd) = adjacent_vertices(*vertexIt, currentGraph);
  for(; neighbourIt != neighbourEnd; ++neighbourIt){
    if (currentGraph[*neighbourIt].number == UNVISITED){
      //We found a tree arc, not yet visited
      strongConnect(neighbourIt, number);
      currentGraph[*vertexIt].lowLink = fmin(currentGraph[*vertexIt].lowLink, currentGraph[*neighbourIt].lowLink);
    } else if (currentGraph[*neighbourIt].number < currentGraph[*vertexIt].number){
      //Frond or cross-link found, we need to check if same SCC
      if (currentGraph[*neighbourIt].onStack == true) {
        currentGraph[*vertexIt].lowLink = fmin(currentGraph[*vertexIt].lowLink, currentGraph[*neighbourIt].number);
      }
    }
  }
  if (currentGraph[*vertexIt].lowLink == currentGraph[*vertexIt].number){
    //We have found the root of the component
    std::vector<int> scc;
    directGraph::vertex_descriptor topStackVertex;
    topStackVertex = verticesStack.top();
    while (!verticesStack.empty() && currentGraph[topStackVertex].number >= currentGraph[*vertexIt].number){
        scc.insert(scc.begin(), topStackVertex);
        currentGraph[topStackVertex].onStack = false;
        verticesStack.pop();
        if (!verticesStack.empty())
          topStackVertex = verticesStack.top();
      }
    //Adding the newly found scc to the list of them
    components.push_back(scc);
  }
}

/*
Function to generate a sample graph used for immediate testing of the algorithm,
not currently used in this version.
*/
directGraph createGraph(){
  directGraph graph;
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
