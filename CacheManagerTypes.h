
//
// Created by boris on 09/01/2020.
//

#ifndef GENERICSERVERSIDE__CACHEMANAGERTYPES_H_
#define GENERICSERVERSIDE__CACHEMANAGERTYPES_H_

#include "CacheManager.h"
#include <string>
#include <map>
#include <list>
#include <fstream>

template<class S>
class FileCacheManager : public CacheManager<string, S> {
  list<pair<string, S>> listCache;
  map<string, typename list<pair<string, S>>::iterator> mapCache;
  unsigned m_capacity = 10;
 public:

  virtual ~FileCacheManager() = default;

  void saveSolution(string key, S obj) {
    string temp;
    auto itr = mapCache.find(key);

    if (itr != mapCache.end()) { //if already in cache.
      listCache.erase(itr->second);
      mapCache.erase(itr);
    } else if (listCache.size() == m_capacity) { //if cache is full.
      temp = prev(listCache.end())->first;
      listCache.erase(prev(listCache.end()));
      mapCache.erase(temp);
    }

    //add the obj.
    pair<string, S> p(key, obj);
    listCache.push_front(p);
    mapCache[key] = listCache.begin();
    ofstream fsout{key, ios::binary | ios::out};
    if (fsout.is_open()) {
      fsout.write((char *) &obj, sizeof(obj));
      fsout.close();
    }
  }

  S getSolution(string key) {
    S tempObj{};
    auto itr = mapCache.find(key);
    if (itr != mapCache.end()) { //if already in cache.
      saveSolution(key, itr->second->second); //in order to update location to front of list.
      itr = mapCache.find(key); //insert may delete the obj. get the itr again.
      return itr->second->second;
    }
    ifstream fsin{key, ios::in | ios::binary};
    if (fsin.is_open()) {
      //this->tempObj = "";
      fsin.read((char *) &tempObj, sizeof(tempObj));
      fsin.close();
      saveSolution(key, tempObj);
      return tempObj;
    } else {
      throw "not found";
    }
  }

  bool isProblemExist(const string &key) {
    try {
      getSolution(key);
      return true;
    } catch (const char *e) {
      return false;
    }
  }

  template<class F>
  void foreach(F function) {
    for (auto itr = listCache.begin(); itr != listCache.end(); ++itr) { //run over the list. ordered.
      function(itr->second);
    }
  }
  // END OF CLASS
};

#endif //GENERICSERVERSIDE__CACHEMANAGERTYPES_H_

