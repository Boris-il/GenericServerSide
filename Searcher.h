//
// Created by boris on 12/01/2020.
//

#ifndef GENERICSERVERSIDE__SEARCHER_H_
#define GENERICSERVERSIDE__SEARCHER_H_

#include "Searchable.h"
#include <queue>
#include <set>
#include <unordered_set>

template<class S>
class ISearcher {
 public:
  virtual State<S> search(Searchable<S> *searchable) = 0;
  virtual int getNumberOfNodesEvaluated() = 0;
};

template<class S>
class Searcher : public ISearcher<S> {
  //priority_queue<State<S>, CompareCost<S>> openList;
  // multiset<State<S>, CostComparator<S>> *openList = new multiset<State<S>, CostComparator<S>>;
  multiset<State<S>> *openList = new multiset<State<S>>;

  int evaluatedNodes = 0;
 public:
  /*Searcher() {
    openList = new multiset<State<S>, CostComparator<State<S>>>;
    evaluatedNodes = 0;
  }*/
  int getOpenListSize() {
    return openList->size();
  }

  void addToOpenList(State<S> state) {
    openList->insert(state);
  }

  bool existInOpenList(State<S> state) {
    for (auto itr = openList->begin(); itr != openList->end(); ++itr) {
      if (state.equals(*itr)) {
        return true;
      }
    }
    return false;
    //return (this->openList->find(state) != this->openList->end());
  }

  void adjustPriorityInOpenList(State<S> state, double new_cost) {
    // erase the element
    this->openList->erase(state);
    // update cost
    state.setSumCost(new_cost);
    // insert back to list
    this->addToOpenList(state);
  }

  State<S> getFromOpenList(State<S> state){
    for (auto itr = openList->begin(); itr != openList->end(); ++itr) {
      if (state.equals(*itr)) {
        return *itr;
      }
    }
    return nullptr;
  }

  void resetSearcher() {
    this->openList->clear();
    this->evaluatedNodes = 0;
  }

  virtual State<S> search(Searchable<S> *searchable) = 0;

  int getNumberOfNodesEvaluated() override {
    return evaluatedNodes;
  }

  bool openContains(State<S> state) {
    return openList->find(state) != openList->end();
  }
 protected:
  State<S> popOpenList() {
    evaluatedNodes++;
    auto itr = prev(openList->end());
    State<S> temp = *itr;
    openList->erase(itr);
    return temp;
  }
};

template<class S>
class BFS : public Searcher<S> {
 public:
  State<S> search(Searchable<S> *searchable) {
    bool foundGoal = false;
    State<S> *goal;
    set<State<S>> close;//init close
    this->addToOpenList(searchable->getInitialState()); //init open
    while (this->getOpenListSize()) {
      State<S> n = this->popOpenList();
      if (searchable->isGoalState(n)) {
        foundGoal = true;
        goal = &n;
        break;
      }
      list<State<S> *> adjacents = searchable->getAllPossible(n);
      /* for (auto itr = adjacents.begin(); itr != adjacents.end(); ++itr) {
         auto pos = close.find(**itr);
         if (pos == close.end() && !this->openContains(**itr)) {
           //todo not i both of lists
           (*itr)->setMCameFrom(&n);
           this->addToOpenList(**itr);
         }
       }*/
      for (auto adj : adjacents) {
        auto pos = close.find(*adj);
        if (!this->existInOpenList(*adj) && pos == close.end()) {
          adj->setMCameFrom(&n);
          this->addToOpenList(*adj);
        }
      }
      close.insert(n);
    }
    if (foundGoal) {
      return *goal;
    } else { //no path from initial to goal.
      return NULL;
    }

  }
};

#endif //GENERICSERVERSIDE__SEARCHER_H_
