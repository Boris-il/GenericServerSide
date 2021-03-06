//
// Created by yuval on 09/01/2020.
//

#ifndef GENERICSERVERSIDE_CMAKE_BUILD_DEBUG_SOLVER_H_
#define GENERICSERVERSIDE_CMAKE_BUILD_DEBUG_SOLVER_H_

template<class P, class S>
class Solver {
  P *m_problem;
  S *m_solution;
 public:
  // constructor
  Solver() {};

  // destructor
  virtual ~Solver() {
    delete (this->m_problem);
    delete (this->m_solution);
  }

  virtual S solve(P *p) = 0;

  virtual Solver *getClone() = 0;
};
#endif //GENERICSERVERSIDE_CMAKE_BUILD_DEBUG_SOLVER_H_
