//
// Created by boris on 09/01/2020.
//

#include "ServerTypes.h"
#include "HandlerTypes.h"
#include "SolverTypes.h"
#include "CacheManagerTypes.h"

int main(int argc, char** argv) {
  server_side::Server *s = new MySerialServer();
  Solver<string, string> *sl = new StringReverser();
  CacheManager<string, string> *m = new FileCacheManager<string>(5);
  ClientHandler *c = new MyTestClientHandler(sl, m);
  s->open(8081, c);
}
