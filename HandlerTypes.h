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
#include "MatrixProblem.h"
#include <sstream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <sys/socket.h>
using namespace std;


class MyTestClientHandler : public ClientHandler {
 public:
  Solver<string, string> *m_solver;
  CacheManager<string> *m_cm;

  void handleClient(int socket);
  MyTestClientHandler(Solver<string, string> *s, CacheManager<string> *m) {
    this->m_solver = s;
    this->m_cm = m;
  }
  int connectToClient();

};
template<class P,class S>
class MyClientHandler : public ClientHandler {
 public:
  Solver<P, S> *m_solver;
  CacheManager<string> *m_cm;
  void handleClient(int socket) {

    string buffer;
    pair<int, int> *start = nullptr, *finish = nullptr;
    bool startFinishFlag = false, finishedBuilding = false;
    std::vector<vector<int>> matrixVector;
    string matrixString = "";
    while (1) {
      std::vector<int> oneRowVector;
      char line[1024] = {0};
      read(socket, line, 1024);
      if (!strcmp(line, "end") || !strcmp(line, "end\n") || !strcmp(line, "end\r\n")) {
        break;
      }
      //string buffer2 = line;
      //buffer += buffer2;
      buffer = line; //added
      string firstN = buffer.substr(0, buffer.find("\n"));
      //matrixStringVector.push_back(firstN);
      matrixString.append(firstN);
      std::stringstream ss(firstN);
      int i;

      while (ss >> i) { //ignor commas and push to vector.
        oneRowVector.push_back(i);
        if (ss.peek() == ',') {
          ss.ignore();
        }
      }
      if (count(firstN.begin(), firstN.end(), ',') == 1 && !startFinishFlag) { //start
        startFinishFlag = true;
        start = new pair<int, int>(oneRowVector.at(0), oneRowVector.at(1));
      } else if (startFinishFlag) { //finish
        finish = new pair<int, int>(oneRowVector.at(0), oneRowVector.at(1));
        finishedBuilding = true;
      } else {
        matrixVector.push_back(oneRowVector);
      }
      if (finishedBuilding) {
        finishedBuilding = false;
        startFinishFlag = false;
        auto *problemMatrix = new MatrixProblem<pair<int, int>>(&matrixVector, start, finish);
        string problem = MatrixProblem<pair<int, int>>::toString(matrixString);
        string solution = "";
        if (this->m_cm->isProblemExist(problem)) {
          solution = this->m_cm->getSolution(problem);
          solution = solution + "\n";
          const char *msg = solution.c_str();
          int is_sent = send(socket, msg, strlen(msg), 0);
          cout << problem << " exist" << endl;
          if (is_sent == -1) {
            cout << "Error sending message" << endl;
          }
        } else {

          solution = this->m_solver->solve(problemMatrix);
          this->m_cm->saveSolution(problem, solution);
          solution = solution + "\n";
          const char *msg = solution.c_str();
          int is_sent = send(socket, msg, strlen(msg), 0);
          cout << problem + " does not exist" << endl;
          if (is_sent == -1) {
            cout << "Error sending message" << endl;
          }
        }
        matrixVector.clear();
        matrixString="";
      }
    }
  }

  MyClientHandler(Solver<P, S> *s, CacheManager<string> *m) {
    this->m_solver = s;
    this->m_cm = m;
  }

};

#endif //GENERICSERVERSIDE__HANDLERTYPES_H_
