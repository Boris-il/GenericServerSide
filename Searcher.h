//
// Created by boris on 12/01/2020.
//

#ifndef GENERICSERVERSIDE__SEARCHER_H_
#define GENERICSERVERSIDE__SEARCHER_H_

#include "Searchable.h"
#include <queue>

template<class S>
class ISearcher {
  virtual S search(Searchable<S> searchable) = 0;
  virtual int getNumberOfNodesEvaluated() = 0;

};

template<class S>
class searcher : public ISearcher<S> {
  priority_queue<State<S>> openList;
  int evaluatedNodes;
 public:
  searcher() {
    openList = new priority_queue<State<S>>;
    evaluatedNodes = 0;
  }
  int getOpenListSize() {
    return openList.size();
  }

  virtual S search(Searchable<S> searchable) override = 0;

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
class BFS : public searcher<S> {

};

#endif //GENERICSERVERSIDE__SEARCHER_H_
