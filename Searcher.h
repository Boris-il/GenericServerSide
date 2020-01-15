//
// Created by boris on 12/01/2020.
//

#ifndef GENERICSERVERSIDE__SEARCHER_H_
#define GENERICSERVERSIDE__SEARCHER_H_

#include "Searchable.h"

template<class S>
class Searcher {
  virtual S search(Searchable<S>) =0;


};

#endif //GENERICSERVERSIDE__SEARCHER_H_
