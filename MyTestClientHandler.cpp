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

int MyTestClientHandler::connectToClient() {
  int socket1 = socket(AF_INET, SOCK_STREAM, 0);
  if (socket1 == -1) {
    cerr << "could not create a socket" << endl;
    close(socket1);
    //return -1;
  }
  string ipStr= "127.0.0.1";
  const char *ipFinal = ipStr.data();

  sockaddr_in address;
  address.sin_family = AF_INET;
  address.sin_addr.s_addr = inet_addr(ipFinal);
  address.sin_port = htons(8081);

  int is_connect = connect(socket1, (struct sockaddr *) &address, sizeof(address));
  if (is_connect == -1) {
    cerr << "Could not connect to host server" << endl;
    // return -2;
  } else {
    cout << "Client is now connected to server" << endl;
  }
  return socket1;
}
void MyTestClientHandler::handleClient(int socket) {
  //int socket1 = connectToClient();
  string buffer;
  while (1) {
    char line[1024] = {0};
    read(socket, line, 1024);
    if (!strcmp(line,"end") || !strcmp(line, "end\n") || !strcmp(line, "end\r\n")){
      break;
    }
    //string buffer2 = line;
    //buffer += buffer2;
    buffer = line; //added
    string firstN = buffer.substr(0, buffer.find("\n"));
    //string secondN = buffer.substr(buffer.find("\n") + 1, buffer.length());
    string problem=firstN, solution;
    auto pos = problem.find('\r');
    problem = problem.substr(0, pos);
    //cout << problem <<endl;
    //cout << "the problem is " << firstN << endl;
    //todo: take firstN and convert it to problem
    if(this->m_cm->isProblemExist(problem)){
      solution = this->m_cm->getSolution(problem);
      solution = solution + "\n";
      const char *msg = solution.c_str();
      int is_sent = send(socket, msg, strlen(msg), 0);
      cout << problem << " exist" << endl;
      if (is_sent == -1) {
        cout << "Error sending message" << endl;
      }
    } else{
      solution = this->m_solver->solve(problem);
      this->m_cm->saveSolution(problem, &solution);
      solution = solution + "\n";
      const char *msg = solution.c_str();
      int is_sent = send(socket, msg, strlen(msg), 0);
      cout << problem + " does not exist" << endl;
      if (is_sent == -1) {
        cout << "Error sending message" << endl;
      }
    }
    //todo: send solution

    //buffer = secondN;
  }

}