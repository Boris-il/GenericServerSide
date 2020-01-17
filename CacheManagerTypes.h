
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

/*template<class S>
class FileCacheManager : public CacheManager<string, S> {
  unsigned int m_capacity;
  unordered_map<string, typename list<pair<string, S>>::iterator> my_cache;
  list<pair<string, S>> lru_list;
  typename list<pair<string, S>>::iterator itr;

 public:
  // constructor
  FileCacheManager(int capacity) {
    this->m_capacity = capacity;
  }

  // destructor
  ~FileCacheManager() {};

  void writeToFile(string key, S *obj) {
    // generate name of file
    //   string fileName = S::class_name;
    string fileName = "";
    //   fileName.append(":");
    fileName.append(key);
    // declare binary file for output
    ofstream output_file{fileName, ios::binary | ios::trunc};
    if (!output_file) {
      cerr << "file create error" << endl;
    } else {
      // write to binary file
      output_file.write((char *) obj, sizeof(*obj));
      // close the file
      output_file.close();
    }
  }

  S readFromFile(string key) {
    S returnObject;
    // generate name of the file to look for
    //   string fileName = S::class_name;
    string fileName = key;
    //   fileName.append(":");
   // fileName.append(key);
    // declare binary file for input
    ifstream input{fileName, ios::binary};
    if (!input) {
      throw "an error";
    } else {
      input.read((char *) &returnObject, sizeof(returnObject));
      input.close();
    }
    return returnObject;
  }

  void saveSolution(string key, S *obj) {
    // check capacity
    if (this->lru_list.size() == this->m_capacity) {
      // position of object to remove
      this->itr = prev(this->lru_list.end());
      // save key to remove from map later
      string key_to_remove = this->itr->first;
      // erase from list
      this->lru_list.erase(this->itr);
      // erase from map using key_to_remove
      this->my_cache.erase(key_to_remove);
    }
    // check if entry already exists in cache
    auto it = my_cache.find(key);
    if (it != this->my_cache.end()) {
      auto val_to_replace = it;
      this->lru_list.erase(val_to_replace->second);
      pair<string, S> p_temp(key, *obj);
      this->lru_list.push_front(p_temp);
      this->itr = lru_list.begin();
      val_to_replace->second = this->itr;
    } else {
      // if not found - create new entry
      pair<string, S> p_temp(key, *obj);
      this->lru_list.push_front(p_temp);
      this->itr = lru_list.begin();
      this->my_cache[key] = this->itr;
    }
    // save/rewrite object to file
    writeToFile(key, obj);
  }

  S &getSolution(string key) {
    S returnObj;
    // search in memory
    auto it = my_cache.find(key);
    if (it != this->my_cache.end()) {
      // check if the element is most recently used
      if (it->second != this->lru_list.begin()) {
        // if not, erase it and push it to front again
        pair<string, S> temp(it->second->first, it->second->second);
        this->lru_list.erase(it->second);
        this->lru_list.push_front(temp);
        this->itr = this->lru_list.begin();
        this->my_cache[key] = this->itr;
        return this->itr->second;
      } else {
        // else it is most recently used, so just return the front
        return it->second->second;
      }
      // search in file system
    } else {
      try {
        returnObj = readFromFile(key);
        // insert file to cache manager
        saveSolution(key, &returnObj);
        return returnObj;
      } catch (const char *e) {
        cerr << "non-exist file" << endl;
        throw e;
      }
    }
  }

  bool isProblemExist(string key) {
    S return_obj;
    try {
      return_obj = getSolution(key);
      return true;
    } catch (const char *e) {
      return false;
    }
  }

  template<class Func>
  void foreach(Func f) {
//    for (auto it = this->my_cache.begin(); it != this->my_cache.end(); ++it) {
//      f(it->second->second);
//   }
    for (auto it = this->lru_list.begin(); it != this->lru_list.end(); ++it) {
      f(it->second);
    }
  }

// END OF CLASS
};*/
/* #############################################################################*/


template<class T>
class FileCacheManager : public CacheManager<T> {
  list<pair<string, T>> listCache;
  map<string, typename list<pair<string, T>>::iterator> mapCache;
  int m_capacity = 5;
  T tempObj;
 public:

  void saveSolution(string key, T obj) {
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
    pair<string, T> p(key, obj);
    listCache.push_front(p);
    mapCache[key] = listCache.begin();
    ofstream fsout{key, ios::binary | ios::out};
    fsout.write((char *) &obj, sizeof(obj));
    fsout.close();
    // READ
    ifstream fsin{key, ios::binary};
    fsin.read((char *) &tempObj, sizeof(tempObj));
    fsin.close();
  }

  T getSolution(string key) {
    auto itr = mapCache.find(key);
    if (itr != mapCache.end()) { //if already in cache.
      saveSolution(key, itr->second->second); //in order to uptade location to front of list.
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
      throw "an error";
    }
  }
  bool isProblemExist(string key) {
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
};

#endif //GENERICSERVERSIDE__CACHEMANAGERTYPES_H_

