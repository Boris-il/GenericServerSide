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
  State(T state) {
    this->m_state = state;
    this->m_cost = 0;
    this->m_cameFrom = nullptr;
  }

  bool equals(State<T> s) {
    return this->m_state->equals(s.m_state);
  }

  T *getMState() const {
    return m_state;
  }
  void setMState(T *m_state) {
    State::m_state = m_state;
  }
  double getMCost() const {
    return m_cost;
  }
  void setMCost(double m_cost) {
    State::m_cost = m_cost;
  }
  State<T> *getMCameFrom() const {
    return m_cameFrom;
  }
  void setMCameFrom(State<T> *m_came_from) {
    m_cameFrom = m_came_from;
  }

};

#endif //GENERICSERVERSIDE__STATE_H_
