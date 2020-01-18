//
// Created by boris on 09/01/2020.
//

#ifndef GENERICSERVERSIDE__SOLVERTYPES_H_
#define GENERICSERVERSIDE__SOLVERTYPES_H_

#include "Solver.h"
#include <string>

using namespace std;

class StringReverser : public Solver<string, string> {
  string m_str;

 public:
  // constructor
  //StringReverser(string str) : m_str(str) {};
  StringReverser() {};

  virtual string solve(string *) override;

};

#endif //GENERICSERVERSIDE__SOLVERTYPES_H_
