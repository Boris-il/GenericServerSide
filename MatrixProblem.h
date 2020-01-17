//
// Created by yuval on 15/01/2020.
//

#ifndef GENERICSERVERSIDE__MATRIXPROBLEM_H_
#define GENERICSERVERSIDE__MATRIXPROBLEM_H_

#include <vector>
#include <string>
#include <climits>
#include "Searchable.h"

template<class T>
class MatrixProblem : public Searchable<T> {
  vector<vector<State<T> * >> m_vect;
  unsigned m_matrix_size;
  State<T> *m_initial;
  State<T> *m_goal;

  State<pair<int, int>> *getMin(list<State<pair<int, int>> *> l) {
    int min = INT_MAX;
    State<pair<int, int>> *s = nullptr;
    for (auto &item : l) {
      if (item->getMCost() < min) {
        s = item;
        l.remove(item);
      }
    }
    return s;
  }

 public:
  // constructor
  MatrixProblem(vector<vector<int>> *input, T *initial, T *goal) {
    this->m_vect = this->createMatrix(input);
    this->m_initial = new State<T>(initial);
    this->m_goal = new State<T>(goal);
  }

  State<T> getInitialState() override {
    return *(this->m_initial);
  }

  bool isGoalState(State<T> state) override {
    return state.equals(*this->m_goal);
  }

  list<State<T> *> getAllPossible(State<T> state) override {
    list<State<pair<int, int>> *> possibilities;
    unsigned boundary = this->m_matrix_size - 1;
    int current_i = state.getMState()->first, current_j = state.getMState()->second;
    State<T> *neighbour = nullptr;

    // check upper cell
    if (current_i - 1 >= 0) {
      neighbour = this->m_vect[current_i - 1][current_j];
      if (neighbour->getMCost() != -1) {
        auto *p = new pair<int, int>(current_i - 1, current_j);
        auto *st = new State<pair<int, int>>(p);
        st->setMCost(neighbour->getMCost());
        possibilities.push_back(st);
      }
    }

    // check bottom cell
    if (current_i + 1 <= boundary) {
      neighbour = this->m_vect[current_i + 1][current_j];
      if (neighbour->getMCost() != -1) {
        auto *p = new pair<int, int>(current_i + 1, current_j);
        auto *st = new State<pair<int, int>>(p);
        st->setMCost(neighbour->getMCost());
        possibilities.push_back(st);
      }
    }
    // check left cell
    if (current_j - 1 >= 0) {
      neighbour = this->m_vect[current_i][current_j - 1];
      if (neighbour->getMCost() != -1) {
        auto *p = new pair<int, int>(current_i, current_j - 1);
        auto *st = new State<pair<int, int>>(p);
        st->setMCost(neighbour->getMCost());
        possibilities.push_back(st);
      }
    }
    // check right cell
    if (current_j + 1 <= boundary) {
      neighbour = this->m_vect[current_i][current_j + 1];
      if (neighbour->getMCost() != -1) {
        auto *p = new pair<int, int>(current_i, current_j + 1);
        auto *st = new State<pair<int, int>>(p);
        st->setMCost(neighbour->getMCost());
        possibilities.push_back(st);
      }
    }

    // sort the list by costs
    /*list<State<pair<int, int>> *> final;
    for (int i = 0; i < possibilities.size(); i++) {
      State<pair<int, int>> *temp = getMin(possibilities);
      final.push_front(temp);
    }*/

    // return sorted list
//    return final;
    return possibilities;
  }

  vector<vector<State<pair<int, int>> * >> createMatrix(vector<vector<int>> *input) {
    vector<vector<State<pair<int, int>> * >> matrix;
    this->m_matrix_size = (*input).size();
    // parse each vector of ints in the vector
    for (int i = 0; i < this->m_matrix_size; i++) {
      vector<State<pair<int, int>> *> single_row;
      for (int j = 0; j < this->m_matrix_size; j++) {
        // create a new state
        auto *new_p = new pair<int, int>(i, j);
        auto *s = new State<pair<int, int>>(new_p);
        int cost = (*input)[i][j];
        s->setMCost((double) cost);
        single_row.push_back(s);
      }
      matrix.push_back(single_row);
    }
    return matrix;
  }

  static string toString(string input) {
    size_t hashP = hash < string > {}(input);
    return to_string(hashP);
  }

  // END OF CLASS
};

#endif //GENERICSERVERSIDE__MATRIXPROBLEM_H_
