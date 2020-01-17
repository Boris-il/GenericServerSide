//
// Created by yuval on 15/01/2020.
//

#ifndef GENERICSERVERSIDE__BESTFIRSTSEARCH_H_
#define GENERICSERVERSIDE__BESTFIRSTSEARCH_H_

#include "Searcher.h"
#include "queue"
#include <unordered_set>

using namespace std;
template<class T>
class BestFirstSearch : public Searcher<T> {
 private:

 public:
  State<T> search(Searchable<T> *searchable) override {
    set<State<T>> closedList;
    this->addToOpenList(searchable->getInitialState());
    while (this->getOpenListSize() > 0) {
      State<T> n = this->popOpenList();
      closedList.insert(n);
      if (searchable->isGoalState(n)) {
        return n;
      }
      // get successors
      list<State<T> *> successors = searchable->getAllPossible(n);
      for (auto statePtr : successors) {
        auto pos = closedList.find(*statePtr);
        if (!this->existInOpenList(*statePtr) && pos == closedList.end()) {
          // update that we came to this successor from n
          statePtr->setMCameFrom(&n);
          // update the cost from n to current successor
          statePtr->setMCost(n.getMCost() + statePtr->getMCost());
        } else {
          // calculate new cost
          int prevCost = statePtr->getMCost();
          int newCost = prevCost + n.getMCost();
          // check if the new path is better than previous
          if (newCost < prevCost) {
            if (!this->existInOpenList(*statePtr)) {
              this->addToOpenList(*statePtr);
            } else {
              // adjust cost of the state in priority list
              this->adjustPriorityInOpenList(*statePtr, newCost);
            }
          }
        }
      }
    }
  }

};

#endif //GENERICSERVERSIDE__BESTFIRSTSEARCH_H_
