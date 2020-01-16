//
// Created by boris on 12/01/2020.
//

#ifndef GENERICSERVERSIDE__SEARCHABLE_H_
#define GENERICSERVERSIDE__SEARCHABLE_H_

#include "State.h"
#include <list>

using namespace std;

template<class T>
class Searchable {

 public:

  virtual State<T> getInitialState() = 0;

  virtual bool isGoalState(State<T>) = 0;

  virtual list<State<T>*> getAllPossible(State<T>) = 0;

};

#endif //GENERICSERVERSIDE__SEARCHABLE_H_
