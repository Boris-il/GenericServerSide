//
// Created by yuval on 18/01/2020.
//

#ifndef GENERICSERVERSIDE__OBJECTADAPTER_H_
#define GENERICSERVERSIDE__OBJECTADAPTER_H_

#include "Solver.h"
#include "Searcher.h"
template <class P>
class ObjectAdapter : public Solver<P,string>{
 public:
  Searcher<pair<int,int>> *m_searcher;
  Searchable<P> *m_searchable;
  ObjectAdapter(Searcher<pair<int, int>> *m_searcher) : m_searcher(m_searcher) {}

  void setSearchable(Searchable<P> *s){
    m_searchable = s;
  }

  string solve(P *p) override {
    /*setSearchable(p);
    State<pair<int,int>> goal = m_searcher->search(m_searchable);
    string directions = ((MatrixProblem<pair<int, int>>) m_searchable).resolveDirections(&goal);*/
    this->m_searcher->resetSearcher();
    State<pair<int,int>> goal = m_searcher->search(p);
    string directions = p->resolve(&goal);
    return directions;
  }

};

#endif //GENERICSERVERSIDE__OBJECTADAPTER_H_
