//
// Created by yuval on 15/01/2020.
//

#ifndef GENERICSERVERSIDE__BESTFIRSTSEARCH_H_
#define GENERICSERVERSIDE__BESTFIRSTSEARCH_H_

#include "Searcher.h"
#include "queue"
using namespace std;
template<class S, class T>
class BestFirstSearch : public Searcher<T>{
  priority_queue<State<T>> *openList;

};







#endif //GENERICSERVERSIDE__BESTFIRSTSEARCH_H_
