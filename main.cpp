/*
Main program for running and testing the three different strong strong_components
algorithms */

#include "tarjan.h"
#include "nuutila.h"
#include "pearce.h"
#include "testing.h"
#include <iostream>

int getChosenSize(int size); //s

int main(){
  /* Selection of the random graphs size on whoch the etsting will be performed.
  The dimension were arbitrarly chosen and are specified in testing.h.
  The random graphs will be dense with a ratio between V and E such that |E| = |V|^2.
  */
  int chosen_size;
  while(true) {
    std::cout << "Please, choose the desired testing graph size: 1 - small, 2 - medium, 3-large: \n";
    std::cin >> chosen_size;
    while (chosen_size < 0 || chosen_size > 3){
      std::cout << "Please, choose the desired testing graph size: 1 - small, 2 - medium, 3-large: \n";
      std::cin >> chosen_size;
    }
    test(getChosenSize(chosen_size), TARJAN);
    test(getChosenSize(chosen_size), NUUTILA);
    test(getChosenSize(chosen_size), PEARCE);
}
}

int getChosenSize(int size){
  switch(size) {
    case 1 : return SMALL_TEST_SIZE;
    case 2 : return MEDIUM_TEST_SIZE;
    case 3 : return LARGE_TEST_SIZE;
  }
}
