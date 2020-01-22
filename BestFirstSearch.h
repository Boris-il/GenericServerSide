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
  Searcher<T> *getClone() override {
    return new BestFirstSearch<T>();
  }

  State<T> search(Searchable<T> *searchable) override {
   cout << "in algo" << endl;
    bool inClose = false;
    multiset<State<T>> closedList;
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
        //cout << "still here" << endl;
        //auto pos = closedList.find(*statePtr);

        for (auto itr = closedList.begin(); itr != closedList.end(); ++itr) {
          if ((*statePtr).equals(*itr)) {
            inClose = true;
            break;
          }
        }

        // check if successor exists in OPEN and CLOSED
        if (!this->existInOpenList(*statePtr) && !inClose) {
          // update that we came to this successor from n
          statePtr->setMCameFrom(&n);
          // update the cost from n to current successor
          statePtr->setSumCost(n.getSumCost() + statePtr->getSumCost());
          // add current successor to OPEN
          this->addToOpenList(*statePtr);
        } else {
          if (inClose) {
            for (auto itr = closedList.begin(); itr != closedList.end(); ++itr) {
              if ((*statePtr).equals(*itr)) {
                *statePtr = *itr;
                break;
              }
            }
          } else {
            *statePtr = this->getFromOpenList(*statePtr);
            //  *statePtr = *pos2;
          }

          inClose = false;
          // calculate new cost
          int prevCost = statePtr->getSumCost();
          int newCost = statePtr->getMCost() + n.getSumCost();
          // check if the new path is better than previous
          if (newCost < prevCost) {
            if (!this->existInOpenList(*statePtr)) {
              this->addToOpenList(*statePtr);
            } else {
              statePtr->setMCameFrom(&n);
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
