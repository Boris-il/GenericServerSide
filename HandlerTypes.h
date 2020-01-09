//
// Created by yuval on 09/01/2020.
//

#ifndef GENERICSERVERSIDE__HANDLERTYPES_H_
#define GENERICSERVERSIDE__HANDLERTYPES_H_

#include "Solver.h"
#include "CacheManager.h"
#include "ClientHandler.h"
#include "SolverTypes.h"
#include "CacheManagerTypes.h"

class MyTestClientHandler : public ClientHandler{
 public:
  Solver<string, string> *m_solver;
  CacheManager<string, string> *m_cm;
  void handleClient(int socket);
  MyTestClientHandler(StringReverser *solver, FileCacheManager<string> *cm) {
    this->m_solver = solver;
    this->m_cm = cm;
  }

};

#endif //GENERICSERVERSIDE__HANDLERTYPES_H_
