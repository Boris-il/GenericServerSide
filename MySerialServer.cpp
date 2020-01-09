//
// Created by yuval on 09/01/2020.
//

#include "ServerTypes.h"

void MySerialServer::open(int port, ClientHandler c) {
  this->m_port=port;
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
  if (listen(socketfd, 5) == -1) {
    cerr << "Error during listening command" << endl;
    // return -3;
  }

  int client_socket1 = accept(socketfd, (struct sockaddr *) &address, (socklen_t *) &address);
  if (client_socket1 == -1) {
    cerr << "Error accepting client" << endl;
    //return -4;
  }
}