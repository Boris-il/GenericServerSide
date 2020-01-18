//
// Created by boris on 12/01/2020.
//

#ifndef GENERICSERVERSIDE__STATE_H_
#define GENERICSERVERSIDE__STATE_H_

#include <algorithm>

template<class T>
class State {
  T *m_state;
  double m_cost;
  double m_sum_cost;
  State<T> *m_cameFrom;

 public:
  // constructor
  State(T *state) {
    this->m_state = state;
    this->m_cost = 0;
    this->m_sum_cost = 0;
    this->m_cameFrom = nullptr;
  }

  bool equals(State<T> s) {
    return *(this->m_state) == *(s.m_state);
  }

  T *getMState() const {
    return m_state;
  }
  void setMState(T *state) {
    State::m_state = state;
  }
  double getMCost() const {
    return m_cost;
  }
  double getSumCost() const {
    return m_sum_cost;
  }

  void setMCost(double cost) {
    this->m_cost = cost;
  }
  void setSumCost(double sum_cost) {
    this->m_sum_cost = sum_cost;
  }

  State<T> *getMCameFrom() const {
    return m_cameFrom;
  }
  void setMCameFrom(State<T> *came_from) {
    State<T> *temp = new State<T>(*came_from);
    this->m_cameFrom = temp;
  }
//  State<T> backTrace() {
//    while(this->m_cameFrom != nullptr) {
//      this->m_state = m_cameFrom;
//    }
//    return *(this->m_state);
//  }

//  bool operator==(const State<T> &obj) const {
//    return (obj.getMCost() == this->m_cost);
//  }

  bool operator<(const State<T> &obj) const {
    return (obj.getMCost() < this->m_cost);
  }

};

template<class T>
struct std::hash<State<T>> {
  size_t operator()(const State<T> &obj) const {
    return hash<double>()(obj.getMCost());
  }
};

//template<class T>
//struct CostComparator {
// public:
//  bool operator()(State<T> & a, State<T> & b) const {
//    return  (a.getMCost() < b.getMCost());
//  }
//};

#endif //GENERICSERVERSIDE__STATE_H_
