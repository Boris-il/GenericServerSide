//
// Created by yuval on 18/01/2020.
//

#ifndef GENERICSERVERSIDE__OBJECTADAPTER_H_
#define GENERICSERVERSIDE__OBJECTADAPTER_H_

#include "Solver.h"
#include "Searcher.h"
#include "BestFirstSearch.h"
#include "search.h";
template<class P, class S>
class ObjectAdapter : public Solver<P, S> {
 public:
  Searcher<pair<int, int>> *m_searcher;
  //P *m_searchable;

  // constructor
  ObjectAdapter(Searcher<pair<int, int>> *m_searcher) : m_searcher(m_searcher) {}

  // destructor
  virtual ~ObjectAdapter() {
    delete (this->m_searcher);
  }

  Solver<P, S> *getClone() override {
    return new ObjectAdapter(m_searcher->getClone());
  }

/*
  void setSearchable(Searchable<P> *s) {
    m_searchable = s;
  }
*/

  S solve(P *p) override {
    cout << "in OA solve" << endl;
    /*setSearchable(p);
    State<pair<int,int>> goal = m_searcher->search(m_searchable);
    string directions = ((MatrixProblem<pair<int, int>>) m_searchable).resolveDirections(&goal);*/
    this->m_searcher->resetSearcher();
    State<pair<int, int>> goal = m_searcher->search(p);
    if (goal.getMState() == nullptr){
      goal = (new BestFirstSearch<pair<int, int>>())->search(p);
      if(goal.getMState() == nullptr){
        goal = (new BFS<pair<int, int>>())->search(p);
        if(goal.getMState() == nullptr){
          goal = (new DFS<pair<int, int>>())->search(p);
        }
      }
    }
    cout <<"got goal" <<endl;
    return goal;
  }

};

#endif //GENERICSERVERSIDE__OBJECTADAPTER_H_
