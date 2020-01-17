//
// Created by boris on 12/01/2020.
//

#ifndef GENERICSERVERSIDE__STATE_H_
#define GENERICSERVERSIDE__STATE_H_

#include <algorithm>

template <class T>
class State {
  T *m_state;
  double m_cost;
  State<T> *m_cameFrom;

 public:
  // constructor
  State(T *state) {
    this->m_state = state;
    this->m_cost = 0;
    this->m_cameFrom = nullptr;
  }

  bool equals(State<T> s) {
    return this->m_state == s.m_state;
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
  void setMCost(double cost) {
    State::m_cost = cost;
  }
  State<T> *getMCameFrom() const {
    return m_cameFrom;
  }
  void setMCameFrom(State<T> *came_from) {
    m_cameFrom = came_from;
  }
//  State<T> backTrace() {
//    while(this->m_cameFrom != nullptr) {
//      this->m_state = m_cameFrom;
//    }
//    return *(this->m_state);
//  }

};

template<class T>
struct CostComparator {
  bool operator()(const State<T> a, const State<T> b) const {
    return a->getMCost() < b->getMCost();
  }
};

#endif //GENERICSERVERSIDE__STATE_H_
