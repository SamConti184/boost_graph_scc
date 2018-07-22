/*
Implementation of the Nuutila algorithm for finding strongly connected components
in a directed graph, as described in the original paper
*/

#include <iostream>
#include "nuutila.h"
using namespace boost;

/*Global variables, used to respect the space complexity of the algorithm:
in order to avoid to fill the call-stack with more than 2 words of memory,
as described in the paper, the following global variables are defined.
They willl be accesse throughout the execution of the algorithm instead of being
passed as reference in the recursive calls. */
std::stack<int> nuutStack;
nuutilaGraph nuutGraph;

//Global variable for keeping the list of strongly connected components.
std::vector<std::vector<int> > nuutComponents;


std::vector<std::vector<int> >  nuutila1(nuutilaGraph &graph){
  nuutGraph = graph;
  nuutilaGraph::vertex_iterator vertexIt, vertexEnd;
  tie(vertexIt, vertexEnd) = vertices(nuutGraph); //Returning iterator for vertices.
  int number = 0;
  //Iteration over vertices
  for(; vertexIt != vertexEnd; ++vertexIt) {
    if (nuutGraph[*vertexIt].number == -1) {
      nuutilaStrongConnect(vertexIt, number);
    }
  }
  std::vector<std::vector<int> > output = nuutComponents;
  nuutComponents.clear();
  return output;
}

void nuutilaStrongConnect (nuutilaGraph::vertex_iterator vertexIt, int &number){
  nuutGraph[*vertexIt].number = number; //number of DFS visit
  nuutGraph[*vertexIt].root = number; // possible root of the SCC for this vertex
  number += 1;
  //DIFFERENCE with Tarjan: here we do not push the vertex on the stack
  nuutilaGraph::adjacency_iterator neighbourIt, neighbourEnd;
  tie(neighbourIt, neighbourEnd) = adjacent_vertices(*vertexIt, nuutGraph);
  for(; neighbourIt != neighbourEnd; ++neighbourIt){
    if (nuutGraph[*neighbourIt].number == -1)
      nuutilaStrongConnect(neighbourIt, number);
    if (!nuutGraph[*neighbourIt].inComponent)
        nuutGraph[*vertexIt].root= fmin(nuutGraph[*vertexIt].root, nuutGraph[*neighbourIt].root);
  }
  if (nuutGraph[*vertexIt].root == nuutGraph[*vertexIt].number){
    //We have found the root of the component
    std::vector<int> scc;
    nuutilaGraph::vertex_descriptor topStackVertex;
    nuutGraph[*vertexIt].inComponent = true; //setting that root it's in a component
    scc.insert(scc.begin(), *vertexIt);
    if(!nuutStack.empty()) //DIFFERENCE - here the stack may be empty, since the root is not on it initially
      topStackVertex = nuutStack.top();
    while (!nuutStack.empty() && nuutGraph[topStackVertex].number >= nuutGraph[*vertexIt].number){
        scc.insert(scc.begin(), topStackVertex);
        nuutGraph[topStackVertex].inComponent = true; //set the other nodes as in the component
        nuutStack.pop();  //Pop the vertex from the stack
        if (!nuutStack.empty())
            topStackVertex = nuutStack.top();
      }
      //Adding the newly found scc to the list of them
      nuutComponents.push_back(scc);
  } else {
    nuutStack.push(*vertexIt); //DIFFERENCE -> we push here on the task, when we know vertex is no root
  }
}

/*
I wasn't able to find a common super-class between adjacency_iterator and
vertex_iterator, so I had to proceed with this not so much elegant solution:
the two functions are the same, only overloaded on the first paramether. */
void nuutilaStrongConnect (nuutilaGraph::adjacency_iterator vertexIt, int &number){
  nuutGraph[*vertexIt].number = number; //number of DFS visit
  nuutGraph[*vertexIt].root = number; // possible root of the SCC for this vertex
  number += 1;
  //DIFFERENCE with Tarjan: here we do not push the vertex on the stack
  nuutilaGraph::adjacency_iterator neighbourIt, neighbourEnd;
  tie(neighbourIt, neighbourEnd) = adjacent_vertices(*vertexIt, nuutGraph);
  for(; neighbourIt != neighbourEnd; ++neighbourIt){
    if (nuutGraph[*neighbourIt].number == -1)
      nuutilaStrongConnect(neighbourIt, number);
    if (!nuutGraph[*neighbourIt].inComponent)
        nuutGraph[*vertexIt].root= fmin(nuutGraph[*vertexIt].root, nuutGraph[*neighbourIt].root);
  }
  if (nuutGraph[*vertexIt].root == nuutGraph[*vertexIt].number){
    //We have found the root of the component
    std::vector<int> scc;
    nuutilaGraph::vertex_descriptor topStackVertex;
    nuutGraph[*vertexIt].inComponent = true; //setting that root it's in a component
    scc.insert(scc.begin(), *vertexIt);
    if(!nuutStack.empty()) //DIFFERENCE - here the stack may be empty, since the root is not on it initially
      topStackVertex = nuutStack.top();
    while (!nuutStack.empty() && nuutGraph[topStackVertex].number >= nuutGraph[*vertexIt].number){
        scc.insert(scc.begin(), topStackVertex);
        nuutGraph[topStackVertex].inComponent = true; //set the other nodes as in the component
        nuutStack.pop();  //Pop the vertex from the stack
        if (!nuutStack.empty())
            topStackVertex = nuutStack.top();
      }
      //Adding the newly found scc to the list of them
      nuutComponents.push_back(scc);
  } else {
    nuutStack.push(*vertexIt); //DIFFERENCE -> we push here on the task, when we know vertex is no root
  }
}

/*
Function to generate a sample graph used for immediate testing of the algorithm
*/
nuutilaGraph createNuutilaGraph(){
  nuutilaGraph graph;
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
