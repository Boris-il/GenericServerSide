//
// Created by boris on 12/01/2020.
//

#ifndef GENERICSERVERSIDE__SEARCHER_H_
#define GENERICSERVERSIDE__SEARCHER_H_

#include "Searchable.h"
#include <queue>
#include <set>
#include <unordered_set>
#include <stack>

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
  virtual Searcher *getClone() = 0;
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

  State<S> getFromOpenList(State<S> state) {
    for (auto itr = openList->begin(); itr != openList->end(); ++itr) {
      if (state.equals(*itr)) {
        return *itr;
      }
    }
    return nullptr;
  }

  void resetSearcher() {
    this->openList->clear();
    //cout << this->evaluatedNodes <<endl;
    this->evaluatedNodes = 0;
  }

  void decEvaluatedNodeNumber() {
    evaluatedNodes++;
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
  Searcher<S> *getClone() {
    return new BFS<S>();
  }

  State<S> search(Searchable<S> *searchable) {
    queue<State<S>> open2;
    bool inClose = false;
    bool foundGoal = false;
    State<S> *goal;
    multiset<State<S>> close;//init close
    //this->addToOpenList(searchable->getInitialState()); //init open
    open2.push(searchable->getInitialState()); //init open
    while (!open2.empty()) {
      //State<S> n = this->popOpenList();
      State<S> n = open2.front();
      open2.pop();
      this->decEvaluatedNodeNumber();
      close.insert(n);
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
        // auto pos = close.find(*adj);
        for (auto itr = close.begin(); itr != close.end(); ++itr) {
          if ((*adj).equals(*itr)) {
            inClose = true;
          }
        }
        if (!inClose) {
          adj->setMCameFrom(&n);
          adj->setSumCost(n.getSumCost() + adj->getSumCost());
          //this->addToOpenList(*adj);
          open2.push(*adj);
          close.insert(*adj);
        }
        inClose = false;
      }
    }
    if (foundGoal) {
      return *goal;
    } else { //no path from initial to goal.
      return NULL;
    }

  }
};

template<class S>
class AStar : public Searcher<S> {
 public:
  Searcher<S> *getClone() override {
    return new AStar<S>();
  }
  State<S> search(Searchable<S> *searchable) {
    bool foundGoal = false, inClose = false;
    multiset<State<S>> close;//init close
    State<S> *goal;

    searchable->getInitialState().setSumCost(0);
    searchable->getInitialState().setH(
        abs(searchable->getGoal().getMState()->first - searchable->getInitialState().getMState()->first)
            + abs(searchable->getGoal().getMState()->second - searchable->getInitialState().getMState()->second));
    this->addToOpenList(searchable->getInitialState());

    while (this->getOpenListSize() > 0) {
      State<S> n = this->popOpenList();
      if (searchable->isGoalState(n)) {
        return n;
      }
      close.insert(n);

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
        double newSum = n.getSumCost() + adj->getMCost();

        for (auto itr = close.begin(); itr != close.end(); ++itr) {
          if ((*adj).equals(*itr)) {
            inClose = true;
          }
        }

        // check if successor exists in OPEN and CLOSED
        if (!this->existInOpenList(*adj) && !inClose) {
          adj->setMCameFrom(&n);
          // update the cost from n to current successor
          adj->setSumCost(newSum);
          adj->setH(adj->getSumCost() + abs(searchable->getGoal().getMState()->first - adj->getMState()->first)
                        + abs(searchable->getGoal().getMState()->second - adj->getMState()->second));
          this->addToOpenList(*adj);

        } else {
          inClose = false;
          if (newSum < adj->getSumCost()) {
            adj->setMCameFrom(&n);
            adj->setSumCost(newSum);
            adj->setH(adj->getSumCost() + abs(searchable->getGoal().getMState()->first - adj->getMState()->first)
                          + abs(searchable->getGoal().getMState()->second - adj->getMState()->second));
            if (!this->existInOpenList(*adj)) {
              this->addToOpenList(*adj);
            }
          }
        }
        if (searchable->isGoalState(*adj)) {
          return *adj;
        }
      }
    }
    /*if (foundGoal) {
      return *goal;
    } else { //no path from initial to goal.
      return NULL;
    }*/
    return NULL;
  }

};

template<class S>
class DFS : public Searcher<S> {
 public:
  Searcher<S> *getClone() override {
    return new DFS<S>();
  }
  State<S> search(Searchable<S> *searchable) override {
    list<State<S>> close;//init close
    stack<State<S>> open2;
    bool inClose = false;

    State<S> startState = searchable->getInitialState();
    close.push_front(startState);

    open2.push(startState);
    // this->decEvaluatedNodeNumber();
    while (!open2.empty()) {
      State<S> n = open2.top();
      open2.pop();
      this->decEvaluatedNodeNumber();

      for (auto itr = close.begin(); itr != close.end(); ++itr) {
        if (n.equals(*itr)) {
          inClose = true;
        }
      }
      if (!inClose) {
        State<S> father = close.front();
        n.setMCameFrom(&father);
        close.push_front(n);
        n.setSumCost(n.getSumCost() + father.getSumCost());
        if (searchable->isGoalState(n)) {
          return n;
        }
      }
      inClose = false;
      list<State<S> *> adjacents = searchable->getAllPossible(n);
      for (auto adj : adjacents) {
        for (auto itr = close.begin(); itr != close.end(); ++itr) {
          if (adj->equals(*itr)) {
            inClose = true;
          }
        }
        if (!inClose) {
          open2.push(*adj);
        }
        inClose = false;
      }
    }



    /*open2.push(searchable->getInitialState()); //init open
    while (!open2.empty()) {
      State<S> n = open2.top();
      open2.pop();
      this->decEvaluatedNodeNumber();


      for (auto itr = close.begin(); itr != close.end(); ++itr) {
        if (n.equals(*itr)) {
          inClose = true;
        }
      }
      if (!inClose) {
        close.insert(n);
        list<State<S> *> adjacents = searchable->getAllPossible(n);
        for (auto adj : adjacents) {
          for (auto itr = close.begin(); itr != close.end(); ++itr) {
            if (adj->equals(*itr)) {
              inClose = true;
            }
          }
          if (!inClose) {
            adj->setMCameFrom(&n);
            adj->setSumCost(n.getSumCost() + adj->getSumCost());
            open2.push(*adj);
          }
          inClose = false;
          if (searchable->isGoalState(*adj)) {
            return *adj;
          }
        }
      }
      inClose = false;
    }
    return NULL;

  }*/
  }
};

#endif //GENERICSERVERSIDE__SEARCHER_H_
