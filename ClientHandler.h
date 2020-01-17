//
// Created by yuval on 09/01/2020.
//

#ifndef GENERICSERVERSIDE__CLIENTHANDLER_H_
#define GENERICSERVERSIDE__CLIENTHANDLER_H_
using namespace std;

class ClientHandler {
 public:
  //todo input and outuput stream.
  virtual void handleClient(int socket) = 0;
};

#endif //GENERICSERVERSIDE__CLIENTHANDLER_H_
