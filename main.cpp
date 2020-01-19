//
// Created by boris on 09/01/2020.
//

#include "ServerTypes.h"
#include "HandlerTypes.h"
#include "SolverTypes.h"
#include "CacheManagerTypes.h"
#include "MatrixProblem.h"
#include "ObjectAdapter.h"
#include "BestFirstSearch.h"

/*
int main(int argc, char** argv) {
  server_side::Server *s = new MySerialServer();
  Solver<string, string> *sl = new StringReverser();
  CacheManager<string> *m = new FileCacheManager<string>();
  ClientHandler *c = new MyTestClientHandler(sl, m);
  s->open(8081, c);
}
*/


namespace boot {
class Main {
 public:
  int main(int port) {
    //create serial server as server
    server_side::Server *s = new MySerialServer();
    //create file cache as cache manager
    CacheManager<string> *m = new FileCacheManager<string>();
    //Solver<string, string> *sl = new StringReverser();
   // Solver<Searchable<pair<int,int>>, string> *oa = new ObjectAdapter<Searchable<pair<int,int>>>(new BestFirstSearch<pair<int,int>>());
    Solver<Searchable<pair<int,int>>, string> *oa = new ObjectAdapter<Searchable<pair<int,int>>>(new BFS<pair<int,int>>());
    //create testClientHandler with string reverser and file cache
    ClientHandler *c = new MyClientHandler<Searchable<pair<int,int>>, string>(oa, m);
    s->open(port, c);
  }
};
}

int main(int argc, char *argv[]) {
  int port = atoi(argv[0]);
  boot::Main main;
  main.main(8081);
};