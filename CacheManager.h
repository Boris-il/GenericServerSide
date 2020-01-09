//
// Created by yuval on 09/01/2020.
//

#ifndef GENERICSERVERSIDE__CACHEMANAGER_H_
#define GENERICSERVERSIDE__CACHEMANAGER_H_

class CacheManager{
  //todo isExist?, get, set.
  //todo Problem Class ? Solution class?
 public:
  virtual bool isProblemExist(Problem p);
  virtual Solution getSolution(Problem p);
  virtual void saveSolution(Problem p, Solution s);
};

class FileCacheManager : public CacheManager{

};

#endif //GENERICSERVERSIDE__CACHEMANAGER_H_
