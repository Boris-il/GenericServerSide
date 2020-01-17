//
// Created by yuval on 09/01/2020.
//
#include <unistd.h>
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstring>
#include "HandlerTypes.h"

void MyTestClientHandler::handleClient(int socket) {
  //int socket1 = connectToClient();
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
    // cin.clear();
    //todo: send solution

    //buffer = secondN;
  }

}


