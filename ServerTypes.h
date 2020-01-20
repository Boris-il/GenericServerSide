//
// Created by boris on 09/01/2020.
//

#ifndef GENERICSERVERSIDE__SERVERTYPES_H_
#define GENERICSERVERSIDE__SERVERTYPES_H_
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include "ClientHandler.h"

// Server interface declaration in namespace
namespace server_side {
class Server {
 public:
  virtual void open(int port, ClientHandler *c) = 0;

  virtual void stop() = 0;
};
}

class MySerialServer : public server_side::Server {

 public:

  virtual void open(int port, ClientHandler *c);
  virtual void stop() {};
};

class MyParallelServer : public server_side::Server {
  virtual void open(int port, ClientHandler *c);
  virtual void stop() {};
};

static void start(int *socket, sockaddr_in *addr, ClientHandler *client_handler);

#endif //GENERICSERVERSIDE__SERVERTYPES_H_
