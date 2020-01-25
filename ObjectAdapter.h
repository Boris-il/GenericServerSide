//
// Created by yuval on 18/01/2020.
//

#ifndef GENERICSERVERSIDE__OBJECTADAPTER_H_
#define GENERICSERVERSIDE__OBJECTADAPTER_H_

#include "Solver.h"
#include "Searcher.h"
#include "BestFirstSearch.h"
#include "search.h"

template<class P, class S>
class ObjectAdapter : public Solver<P, S> {
 public:
  Searcher<pair<int, int>> *m_searcher;

  // constructor
  ObjectAdapter(Searcher<pair<int, int>> *searcher) : m_searcher(searcher) {}

  // destructor
  virtual ~ObjectAdapter() {
    delete (this->m_searcher);
  }

  Solver<P, S> *getClone() override {
    return new ObjectAdapter(m_searcher->getClone());
  }

  S solve(P *p) override {
    // reset the searcher for next run
    this->m_searcher->resetSearcher();
    // search for path to goal
    State<pair<int, int>> goal = m_searcher->search(p);

    // try another algorithm if path wasn't found
    if (goal.getMState() == nullptr) {
      goal = (new BestFirstSearch<pair<int, int>>())->search(p);
      if (goal.getMState() == nullptr) {
        goal = (new BFS<pair<int, int>>())->search(p);
        if (goal.getMState() == nullptr) {
          goal = (new DFS<pair<int, int>>())->search(p);
        }
      }
    }
    return goal;
  }

};

#endif //GENERICSERVERSIDE__OBJECTADAPTER_H_
