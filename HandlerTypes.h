//
// Created by yuval on 09/01/2020.
//

#ifndef GENERICSERVERSIDE__HANDLERTYPES_H_
#define GENERICSERVERSIDE__HANDLERTYPES_H_

#include "Solver.h"
#include "CacheManager.h"
#include "ClientHandler.h"

class MyTestClientHandler : public ClientHandler{
 public:
  Solver solver;
  CacheManager cm;
  void handleClient(int socket);
  MyTestClientHandler(const Solver &solver, const CacheManager &cm);

};

#endif //GENERICSERVERSIDE__HANDLERTYPES_H_
