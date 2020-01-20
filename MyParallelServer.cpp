//
// Created by yuval on 20/01/2020.
//

#include "ServerTypes.h"
#include <thread>

void parallelClient(int *client_socket1, ClientHandler *c){
  c->handleClient(*client_socket1); //handle client
  close(*client_socket1); //finish, so close the connection with client
}

void startP(int *socketfd, sockaddr_in *address, ClientHandler *c){

  unsigned len = sizeof(*address);
  socklen_t *addrlen = &len;

  struct timeval tv;
  tv.tv_sec = 60;
  tv.tv_usec = 0;
  int socketNum = *socketfd;
  while (1) {

    //accept
    int client_socket1 = accept(socketNum, (struct sockaddr *) &address, addrlen);

    if (client_socket1 == -1) {
      cerr << "Error accepting client" << endl;
      //break ???
      break;
      //return -4;
    } else {
      std::thread tp(parallelClient, &client_socket1, c);
      tp.detach();
      setsockopt(socketNum, SOL_SOCKET, SO_RCVTIMEO, (const char *) &tv, sizeof tv); // create timeout to next client
    }

  }

  close(socketNum);

}

void MyParallelServer::open(int port, ClientHandler *c) {
  cout << "starting socket" << endl;
  int socketfd = socket(AF_INET, SOCK_STREAM, 0);
  if (socketfd == -1) {
    cerr << "could not create a socket" << endl;
    //return -1;
  }
  //close(socketfd);
  sockaddr_in address{};
  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port = htons(port);
  if (bind(socketfd, (struct sockaddr *) &address, sizeof(address)) == -1) {
    cerr << "Could not bind the socket to an IP" << endl;
    close(socketfd);
    //return -2;
  }
  struct timeval tv;
  tv.tv_sec = 60;
  tv.tv_usec = 0;
  setsockopt(socketfd, SOL_SOCKET, SO_RCVTIMEO, (const char *) &tv, sizeof tv);

  if (listen(socketfd, 5) == -1) {
    cerr << "Error during listening command" << endl;
    // return -3;
  }

  std::thread t1(startP, &socketfd, &address, c);
  this_thread::sleep_for(chrono::seconds(1));
  t1.join();
}
