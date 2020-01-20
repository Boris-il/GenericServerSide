//
// Created by yuval on 09/01/2020.
//

#ifndef GENERICSERVERSIDE__CACHEMANAGER_H_
#define GENERICSERVERSIDE__CACHEMANAGER_H_

#include <string>
#include <unordered_map>
#include <list>
#include <iostream>
#include <fstream>


//todo isExist?, get, set.
//todo Problem Class ? Solution class?
//  virtual bool isProblemExist(Problem p);
//  virtual Solution getSolution(Problem p);
//  virtual void saveSolution(Problem p, Solution s);
using namespace std;

template<class P, class S>
class CacheManager {
 public:
  virtual bool isProblemExist(const P &) = 0;
  virtual S getSolution(P) = 0;
  virtual void saveSolution(P, S) = 0;
};

#endif //GENERICSERVERSIDE__CACHEMANAGER_H_
