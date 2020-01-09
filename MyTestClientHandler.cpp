//
// Created by yuval on 09/01/2020.
//
#include <unistd.h>
#include <string>
#include "HandlerTypes.h"

void MyTestClientHandler::handleClient(int socket) {
  string buffer = "";
  bool x = true;
  while (x) {
    char line[1024] = {0};
    read(socket, line, 1024);
    string buffer2 = line;
    buffer = buffer + buffer2;
    string firstN = buffer.substr(0, buffer.find("\n"));
    string secondN = buffer.substr(buffer.find("\n") + 1, buffer.length());
    string problem=firstN, solution;
    //todo: take firstN and convert it to problem
    if(this->m_cm->isProblemExist(problem)){
      solution = this->m_cm->getSolution(problem);
    } else{
      solution = this->m_solver->solve(problem);
      this->m_cm->saveSolution(problem, &solution);
    }
    //todo: send solution

    buffer = secondN;
  }

}