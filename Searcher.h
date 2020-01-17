//
// Created by boris on 12/01/2020.
//

#ifndef GENERICSERVERSIDE__SEARCHER_H_
#define GENERICSERVERSIDE__SEARCHER_H_

#include "Searchable.h"
#include <queue>
#include <set>

template<class S>
class ISearcher {
 public:
  virtual State<S> search(Searchable<S> searchable) = 0;
  virtual int getNumberOfNodesEvaluated() = 0;

};

template<class S>
class Searcher : public ISearcher<S> {
  //priority_queue<State<S>, CompareCost<S>> openList;
  multiset<State<S>, CostComparator<State<S>>> openList;
  int evaluatedNodes;
 public:
  Searcher() {
    openList = new multiset<State<S>, CostComparator<State<S>>>;
    evaluatedNodes = 0;
  }
  int getOpenListSize() {
    return openList.size();
  }

  void addToOpenList(State<S> state) {
    openList.push(state);
  }

  bool existInOpenList(State<S> state) {
    return (this->openList.find(state) != this->openList.end());
  }

  void adjustPriorityInOpenList(State<S> state, double new_cost) {
    // erase the element
    this->openList.erase(state);
    // update cost
    state.setMCost(new_cost);
    // insert back to list
    this->addToOpenList(state);
  }

  virtual State<S> search(Searchable<S> searchable) override = 0;

  int getNumberOfNodesEvaluated() override {
    return evaluatedNodes;
  }
 protected:
  State<S> popOpenList() {
    evaluatedNodes++;
    return openList.pop();
  }
};

template<class S>
class BFS : public Searcher<S> {

};

#endif //GENERICSERVERSIDE__SEARCHER_H_
