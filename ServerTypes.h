//
// Created by boris on 09/01/2020.
//

#ifndef GENERICSERVERSIDE__SERVERTYPES_H_
#define GENERICSERVERSIDE__SERVERTYPES_H_
#include <iostream>
#include <bits/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include "ClientHandler.h"

// Server interface declaration in namespace
namespace server_side {
class Server {
 public:
  virtual void open(int port, ClientHandler c);

  virtual void stop();
};
}

class MySerialServer : public server_side::Server {

  int m_port;
 public:

  //todo implement
  virtual void open(int port, ClientHandler c);
  virtual void stop();
  void start();
  int getPort();


};


#endif //GENERICSERVERSIDE__SERVERTYPES_H_
