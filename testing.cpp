/*
Module for testing the three algorithms. The main function returns the average
time of execution for the chosen algorithm and the chosen graph dimension,
as arbitrarly defined in testing.h.
The tetsin phase in based on generating  a selected number of random graphs
(using a Boost graph method) and checking if the identified
strong connected components are the same as the ones identified by the Boost
implementation of the Tarjan algorithm.
*/

#include "tarjan.h"
#include "nuutila.h"
#include "pearce.h"
#include "testing.h"

int test_size;
static randGen rng(static_cast<unsigned int>(std::time(0)));

void test(int chosen_test_size, int algorithm) {
  int time = 0;
  int average_time = 0;
  test_size = chosen_test_size;

  for(int i = 0; i < NUMBER_OF_TESTING_GRAPHS; i++){
    time += randGraphsTest(algorithm, i);
  }
  average_time = time / NUMBER_OF_TESTING_GRAPHS;
  std::cout << "The average execution time is: " << (float(average_time)/CLOCKS_PER_SEC) << "ms.\n";
}

int randGraphsTest(int algorithm, int num){
  clock_t clkStart;
  clock_t clkFinish;

  std::vector<int> boost_scc(test_size);
  std::vector<std::vector<int> > algorithm_scc;

  int num_scc;

/*Depending on the chosen algorithm, we create a different type of graph (as different
graph requires a different VertexProperty in this implementation) and perform the selected
algorithm on a random graph created by Boost. */
  if(algorithm == TARJAN) {
                  directGraph g;
                  directGraph::vertices_size_type V = test_size;
                  generate_random_graph (g, V, (test_size*test_size), rng, false, true); //allow self-edges
                  strong_components(g, make_iterator_property_map(boost_scc.begin(), get(vertex_index, g), boost_scc[0]));
                  clkStart = clock(); //Timing of the algorithm execution
                  algorithm_scc = tarjan(g);
                  clkFinish = clock();
  } else if(algorithm == NUUTILA) {
                  nuutilaGraph g;
                  nuutilaGraph::vertices_size_type V = test_size;
                  generate_random_graph (g, V, (test_size*test_size), rng, false, true); //allow self-edges
                  strong_components(g, make_iterator_property_map(boost_scc.begin(), get(vertex_index, g), boost_scc[0]));
                  clkStart = clock();
                  algorithm_scc = nuutila1(g);
                  clkFinish = clock();
  } else if(algorithm == PEARCE) {
                  pearceGraph g;
                  pearceGraph::vertices_size_type V = test_size;
                  generate_random_graph (g, V, (test_size*test_size), rng, false, true); //allow self-edges
                  strong_components(g, make_iterator_property_map(boost_scc.begin(), get(vertex_index, g), boost_scc[0]));
                  clkStart = clock();
                  algorithm_scc = pearce(g);
                  clkFinish = clock();
  }

  /*Boost graph implementation of tarjan through strong_components() saves in the
  vector boost_scc (of dimension = |V|) passed as argument the number of the corresponding
  connected component per each vertex. E.g, if vertex 0 is in component 3, then
  boost_scc[0] = 3. We modify our algorithms' output to match this structure. */
  int cont = 0;
  int index = 0;
  std::vector<int> proposed_scc(test_size);
  for(std::vector<std::vector<int> >::iterator j=algorithm_scc.begin(); j != algorithm_scc.end(); j++) {
    for (std::vector<int>::iterator it = j->begin(); it != j->end(); ++it){
      index = *it;
      proposed_scc[index] = cont;
    }
    cont++;
  }

  if (boost_scc != proposed_scc){
    std::cout << "The " << getAlgorithm(algorithm) << " algorithm was incorrect in test " << num << ".\n";
  }
  else {
    std::cout << "The " << getAlgorithm(algorithm) << " algorithm was correct in test " << num << ".\n";
/*
Following code can be used for debugging, checking the difference between the two vectors:
    for (std::vector<int>::iterator it = boost_scc.begin(); it != boost_scc.end(); ++it)
        std::cout << *it << " - ";
        std::cout <<"\n";
    for (std::vector<int>::iterator j = proposed_scc.begin(); j != proposed_scc.end(); ++j)
        std::cout << *j << " - "; */
}

  return (clkFinish - clkStart);
}

std::string getAlgorithm(int alg){
  switch(alg){
    case TARJAN: return "Tarjan";
    case NUUTILA: return "Nuutila";
    case PEARCE: return "Pearce";
  }
}
