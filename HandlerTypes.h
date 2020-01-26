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
#include "ObjectAdapter.h"
#include "BestFirstSearch.h"
#include <sstream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <sys/socket.h>
using namespace std;

template<class P, class S, class T>
class MyTestClientHandler : public ClientHandler {
 public:
  Solver<P, S> *m_solver;
  CacheManager<T, S> *m_cm;

  // constructor
  MyTestClientHandler(Solver<string, string> *solver, CacheManager<T, S> *cm) {
    this->m_solver = solver;
    this->m_cm = cm;
  }

  void handleClient(int socket) override {
    string buffer;
    while (1) {
      char line[1024] = {0};
      read(socket, line, 1024);
      if (!strcmp(line, "end") || !strcmp(line, "end\n") || !strcmp(line, "end\r\n")) {
        break;
      }
      //string buffer2 = line;
      //buffer += buffer2;
      buffer = line; //added
      string firstN = buffer.substr(0, buffer.find("\n"));
      //string secondN = buffer.substr(buffer.find("\n") + 1, buffer.length());
      string problem = firstN, solution = "";
      auto pos = problem.find('\r');
      problem = problem.substr(0, pos);
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
        solution = this->m_solver->solve(&problem);
        this->m_cm->saveSolution(problem, solution);
        solution = solution + "\n";
        const char *msg = solution.c_str();
        int is_sent = send(socket, msg, strlen(msg), 0);
        cout << problem + " does not exist" << endl;
        if (is_sent == -1) {
          cout << "Error sending message" << endl;
        }
      }
      // cin.clear();
      //todo: send solution

      //buffer = secondN;
    }
  }

};

template<class P, class S, class T>
class MyClientHandler : public ClientHandler {
 public:
  Solver<P, S> *m_solver;
  CacheManager<T, S> *m_cm;

  // destructor
  ~MyClientHandler() override {};

  // constructor
  MyClientHandler(Solver<P, S> *solver, CacheManager<T, S> *cm) {
    this->m_solver = solver;
    this->m_cm = cm;
  }

  ClientHandler *getClone() override {
    return new MyClientHandler(this->m_solver->getClone(), this->m_cm);
  }

  void handleClient(int socket) override {
    string buffer = "";
    pair<int, int> *start = nullptr, *finish = nullptr;
    bool startFinishFlag = false, finishedBuilding = false;
    vector<vector<int>> matrixVector;
    string matrixString;
    bool x = true;
    int counter = 0;
    while (x) {
      vector<int> oneRowVector;
      char line[4096] = {0};

      // read user input - single line
      read(socket, line, 4096);
      //cout << line << endl;
      string checker = line;
      auto foundEnd = checker.find("end");
      if (foundEnd != string::npos) {
        x = false;
      }
      auto found2 = checker.find(',');
      if (found2 == string::npos) {
        // cout << line << endl;
        continue;
      }
      string buffer2 = line; //###

      buffer += buffer2; //###
      //buffer = line; //added ####
      string firstN = buffer.substr(0, buffer.find("\n"));
      string secondN = buffer.substr(buffer.find("\n") + 1, buffer.length()); //###
      //matrixStringVector.push_back(firstN);

      matrixString.append(firstN);
      //  cout << firstN << endl;
      int numberOfCommas = count(firstN.begin(), firstN.end(), ',');
      // cerr << numberOfCommas << endl;
      stringstream ss(firstN);
      int i;

      while (ss >> i) { //ignore commas and push to vector.
        oneRowVector.push_back(i);
        if (ss.peek() == ',') {
          ss.ignore();
        }
      }
      if (numberOfCommas < 1) {
        continue;
      }

      if (numberOfCommas > 1) {
        matrixVector.push_back(oneRowVector);
        counter++;
      } else if (numberOfCommas == 1 && !startFinishFlag) {
        startFinishFlag = true;
        start = new pair<int, int>(oneRowVector.at(0), oneRowVector.at(1));
      } else if (numberOfCommas == 1 && startFinishFlag) {
        finish = new pair<int, int>(oneRowVector.at(0), oneRowVector.at(1));
        finishedBuilding = true;
      }

      if (finishedBuilding) {
        finishedBuilding = false;
        startFinishFlag = false;
        string solution_str, problem;
        S solutionObj{};

        // construct the matrix
        auto *problemMatrix = new MatrixProblem<pair<int, int>>(&matrixVector, start, finish);

        // cast the matrix to string
        problem = MatrixProblem<pair<int, int>>::toString(matrixString);

        // send the string to FileCacheManager to check if the problem exists
        if (this->m_cm->isProblemExist(problem)) {
          //cout << problem << " problem exists" << endl;
          // if exists, get the solution
          solutionObj = this->m_cm->getSolution(problem);
        } else {
          //cout << problem + " problem does NOT exist" << endl;
          // if doesn't exists, solve and save solution
          solutionObj = this->m_solver->solve(problemMatrix);
          this->m_cm->saveSolution(problem, solutionObj);
        }
        solutionObj = this->m_solver->solve(problemMatrix);//###
        try {
          solution_str = problemMatrix->resolve(&solutionObj) + "\n";

        } catch (const char *c) {
          solution_str = "NO PATH AVAILABLE\n";
        }

        // resolve solution object to string

        // create message to send to client
        const char *msg = solution_str.c_str();
        // send the message
        int is_sent = send(socket, msg, strlen(msg), 0);
        if (is_sent == -1) {
          cout << "Error sending message" << endl;
        }
        // clear the matrix vector to fit the next matrix
        matrixVector.clear();
        // clear the matrix string representation
        matrixString = "";
      }
      buffer = secondN; //###
    }
  }

};

#endif //GENERICSERVERSIDE__HANDLERTYPES_H_
