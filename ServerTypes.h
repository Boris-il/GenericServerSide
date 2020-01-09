//
// Created by boris on 09/01/2020.
//

#ifndef GENERICSERVERSIDE__SERVERTYPES_H_
#define GENERICSERVERSIDE__SERVERTYPES_H_

// Server interface declaration in namespace
namespace server_side {
class Server {
 public:
  virtual void open(int port, ClientHander c);

  virtual void stop();
};
}

class MySerialServer : public server_side::Server {

  //todo implement

};


#endif //GENERICSERVERSIDE__SERVERTYPES_H_
