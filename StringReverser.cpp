//
// Created by boris on 09/01/2020.
//

#include "SolverTypes.h"
#include <string>

using namespace std;

string StringReverser::solve(string &str) {
  unsigned input_len = str.length();
  // swap characters starting from two corners
  for (unsigned i = 0; i < (input_len / 2); i++) {
    swap(str[i], str[input_len - i - 1]);
  }
}