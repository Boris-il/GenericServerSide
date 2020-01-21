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

namespace boot {
class Main {
 public:
  int main(int port) {
    //create serial server as server
    server_side::Server *s = new MyParallelServer();
    // create a Cache Manager as a FileCacheManager that gets: Problem as a string, Solution as a State of pair
    CacheManager<string, State<pair<int, int>>> *m = new FileCacheManager<State<pair<int, int>>>();

    //Solver<string, string> *sl = new StringReverser();

    // solve using bestFS
    Solver<Searchable<pair<int, int>>, State<pair<int, int>>>
      *oa = new ObjectAdapter<Searchable<pair<int, int>>, State<pair<int, int>>>(new BestFirstSearch<pair<int, int>>());
    // solve using AStar
    Solver<Searchable<pair<int, int>>, State<pair<int, int>>>
      *oa2 = new ObjectAdapter<Searchable<pair<int, int>>, State<pair<int, int>>>(new AStar<pair<int, int>>());
    // solve using BFS
    Solver<Searchable<pair<int, int>>, State<pair<int, int>>>
        *oa3 = new ObjectAdapter<Searchable<pair<int, int>>, State<pair<int, int>>>(new BFS<pair<int, int>>());
    // solve using DFS
    Solver<Searchable<pair<int, int>>, State<pair<int, int>>>
        *oa4 = new ObjectAdapter<Searchable<pair<int, int>>, State<pair<int, int>>>(new DFS<pair<int, int>>());

    ClientHandler *c = new MyClientHandler<Searchable<pair<int, int>>, State<pair<int, int>>, string>(oa, m);
    s->open(port, c);
  }
};

}

int main(int argc, char *argv[]) {
  //int port = atoi(argv[0]);
  boot::Main main;
  main.main(5600);
};