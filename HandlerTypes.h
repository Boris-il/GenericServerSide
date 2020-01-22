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
      //cout << problem <<endl;
      //cout << "the problem is " << firstN << endl;
      //todo: take firstN and convert it to problem
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

// P = Problem, S = Solution, T = Input Format For Problem From CacheManager
template<class P, class S, class T>
class MyClientHandler : public ClientHandler {
 public:
  Solver<P, S> *m_solver;
  CacheManager<T, S> *m_cm;

  // constructor
  MyClientHandler(Solver<P, S> *solver, CacheManager<T, S> *cm) {
    this->m_solver = solver;
    this->m_cm = cm;
  }

  ClientHandler *getClone() override {
    cout << "clone" << endl;
    return new MyClientHandler(this->m_solver->getClone(), this->m_cm);
  }

  void handleClient(int socket) override {
    /*int index = 0;

    int matrixRow = 0;
    int matrixCol = 0;
    string buffer = "";
    pair<int, int> *start = nullptr, *finish = nullptr;
    bool startFinishFlag = false, finishedBuilding = false;
    vector<vector<int>> matrixVector;
    string matrixString;
    while (1) {
      vector<int> oneRowVector;
      char line[1024] = {0};
      if (buffer.find("end\n") == string::npos) {
        read(socket, line, 1024);
      }

      string secondBuffer = line;
      buffer = buffer + secondBuffer;
      const string firstPart = buffer.substr(0, buffer.find("\n")); //all tha values from start to \n
      int startSecondPart = buffer.find("\n") + 1;
      string secondPart = buffer.substr(
          startSecondPart, buffer.length()); //all the values from \n to end
      string currentLine = firstPart;
      if (firstPart == "end") {
        //we finish the reading of the file
        break;
      } else {
        //if its the first line we read we will count the column in the matrix by the ","
        if (matrixRow == 0) {
          matrixCol = count(firstPart.begin(), firstPart.end(), ',') + 1;
        }
        if (count(firstPart.begin(), firstPart.end(), ',') + 1 == matrixCol) {
          //we will insert every line of the matrix to the vector
          stringstream ss(firstPart);
          int i;

          while (ss >> i) { //ignore commas and push to vector.
            oneRowVector.push_back(i);
            if (ss.peek() == ',') {
              ss.ignore();
            }
          }
          matrixRow += 1;
          matrixVector.push_back(oneRowVector);
        } else {
          stringstream ss(firstPart);
          string valStr;
          vector<int> values;
          int k = 0;
          while (getline(ss, valStr, ',')) {
            int val = stoi(valStr);
            values.push_back(val);
            k++;
          }
          if (index == 0) {
            //we are in the line of the start position
            start = new pair<int, int>(values.at(0), values.at(1));
            index += 1;
          } else {
            //we are in the line of the end position
            finish = new pair<int, int>(values.at(0), values.at(1));
          }

        }
      }
      buffer = secondPart;

    }
    string solution_str, problem;
    S solutionObj{};

    // construct the matrix
    auto *problemMatrix = new MatrixProblem<pair<int, int>>(&matrixVector, start, finish);

    // cast the matrix to string
    problem = MatrixProblem<pair<int, int>>::toString(matrixString);
    //cout <<matrixString<<endl;
    cout << problemMatrix->getGoal().getMState()->first << "," << problemMatrix->getGoal().getMState()->second << endl;

    // send the string to FileCacheManager to check if the problem exists
    */
    /* if (this->m_cm->isProblemExist(problem)) {
        cout << problem << " problem exists" << endl;
    // if exists, get the solution
    solutionObj = this->m_cm->getSolution(problem);
  } else {
    cout << problem + " problem does NOT exist" << endl;
    // if doesn't exists, solve and save solution
    solutionObj = this->m_solver->solve(problemMatrix);
    this->m_cm->saveSolution(problem, solutionObj);
  }*/
    /*
  solutionObj = this->m_solver->solve(problemMatrix); //###
  // resolve solution object to string
  solution_str = problemMatrix->resolve(&solutionObj) + "\n";
  solution_str.append("Nodes Evaluated: " + to_string(((ObjectAdapter<Searchable<pair<int, int>>,
                                                                      State<pair<int,
                                                                                 int>>> *) this->m_solver)->m_searcher->getNumberOfNodesEvaluated())
  + "\n");
  // create message to send to client
  const char *msg = solution_str.c_str();
  // send the message
  int is_sent = send(socket, msg, strlen(msg), 0);
  if (is_sent == -1) {
    cout << "Error sending message" << endl;
  }
  // clear the matrix vector to fit the next matrix
  //matrixVector.clear();



*/

    //#######################################################################################################

    cout << "in handle" << endl;
    string buffer = "";
    pair<int, int> *start = nullptr, *finish = nullptr;
    bool startFinishFlag = false, finishedBuilding = false;
    vector<vector<int>> matrixVector;
    string matrixString;
    bool x = true;
    int counter = 0;
    while (x) {
      vector<int> oneRowVector;
      char line[1024] = {0};

      // read user input - single line
      read(socket, line, 1024);
      //cout << line << endl;
      if (!strcmp(line, "end") || !strcmp(line, "end\n") || !strcmp(line, "end\r\n") || !strcmp(line, "\n")
          || !strcmp(line, "\r\n")) {
        break;
      }
      string checker = line;
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
      auto found = firstN.find("end");
      if (found != string::npos) {
        break;
      }
      if (firstN == "end") {
        break;
      }

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


      /*if (numberOfCommas == 1 && !startFinishFlag) { //start
        startFinishFlag = true;
        start = new pair<int, int>(oneRowVector.at(0), oneRowVector.at(1));
      } else if (startFinishFlag) { //finish
        finish = new pair<int, int>(oneRowVector.at(0), oneRowVector.at(1));
        finishedBuilding = true;
      } else {
        matrixVector.push_back(oneRowVector);
      }*/

      if (finishedBuilding) {
        cerr << counter << endl;
        finishedBuilding = false;
        startFinishFlag = false;
        string solution_str, problem;
        S solutionObj{};

        // construct the matrix
        auto *problemMatrix = new MatrixProblem<pair<int, int>>(&matrixVector, start, finish);

        // cast the matrix to string
        problem = MatrixProblem<pair<int, int>>::toString(matrixString);
        //    cout << matrixString << endl;
        //    cout << problemMatrix->getGoal().getMState()->first << "," << problemMatrix->getGoal().getMState()->second
        //         << endl;

        // send the string to FileCacheManager to check if the problem exists
        /* if (this->m_cm->isProblemExist(problem)) {
           cout << problem << " problem exists" << endl;
           // if exists, get the solution
           solutionObj = this->m_cm->getSolution(problem);
         } else {
           cout << problem + " problem does NOT exist" << endl;
           // if doesn't exists, solve and save solution
           solutionObj = this->m_solver->solve(problemMatrix);
           this->m_cm->saveSolution(problem, solutionObj);
         }*/
        solutionObj = this->m_solver->solve(problemMatrix); //###
        // resolve solution object to string
        solution_str = problemMatrix->resolve(&solutionObj) + "\n";
        solution_str.append("Nodes Evaluated: " + to_string(((ObjectAdapter<Searchable<pair<int, int>>,
                                                                            State<pair<int,
                                                                                       int>>> *) this->m_solver)->m_searcher->getNumberOfNodesEvaluated())
                                + "\n");
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
