//Test.h
#ifndef testing_h
#define testing_h

#include "boost/random.hpp"
#include <boost/graph/random.hpp>
#include <boost/graph/strong_components.hpp>
#include <time.h>

//Numbers arbitraly chosen: good compromises between time required and modest dimensions.
#define NUMBER_OF_TESTING_GRAPHS 30
#define SMALL_TEST_SIZE 15
#define MEDIUM_TEST_SIZE 150
#define LARGE_TEST_SIZE 500

#define TARJAN 1
#define NUUTILA 2
#define PEARCE 3


typedef boost::mt19937 randGen; //a chosen random generator, used in generating random graphs.

void test(int chosen_test_size, int algorithm);
int randGraphsTest(int algorithm, int num);
std::string getAlgorithm(int alg);

#endif
