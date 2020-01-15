//
// Created by yuval on 15/01/2020.
//

#ifndef GENERICSERVERSIDE__MATRIXPROBLEM_H_
#define GENERICSERVERSIDE__MATRIXPROBLEM_H_

#include "Searchable.h"



template<class T>
class MatrixProblem : public Searchable<T>{
 public:
  State<T> getInitialState() override {

  }
  bool isGoalState(State<T> state) override {
    return false;
  }
  list<State<T>> getAllPossible(State<T> state) override {
    return list<State<T>>();
  }

};


#endif //GENERICSERVERSIDE__MATRIXPROBLEM_H_
