#include <unistd.h>
#include <cstring>
#include <sstream>
#include <vector>
#include <algorithm>
#include <sys/socket.h>
#include "HandlerTypes.h"
#include "MatrixProblem.h"
#include "BestFirstSearch.h"
using namespace std;
//
// Created by yuval on 15/01/2020.
//
void MyClientHandler::handleClient(int socket) {
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
        // TEST - CHECK BEST FS
        /*ISearcher<pair<int, int>> *bestFS = new BestFirstSearch<pair<int, int>>();
        bestFS->search(problemMatrix);*/
        //TEST - CHECK BFS
        ISearcher<pair<int, int>> *bfs = new BFS<pair<int, int>>();
        State<pair<int, int>> goal = bfs->search(problemMatrix);
        problemMatrix->resolveDirections(&goal);
        //this->m_solver = bfs;


        // END OF TEST
        solution = this->m_solver->solve(problem);
        this->m_cm->saveSolution(problem, solution);
        solution = solution + "\n";
        const char *msg = solution.c_str();
        int is_sent = send(socket, msg, strlen(msg), 0);
        cout << problem + " does not exist" << endl;
        if (is_sent == -1) {
          cout << "Error sending message" << endl;
        }
      }
    }
  }
}