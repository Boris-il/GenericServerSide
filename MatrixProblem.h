//
// Created by yuval on 15/01/2020.
//

#ifndef GENERICSERVERSIDE__MATRIXPROBLEM_H_
#define GENERICSERVERSIDE__MATRIXPROBLEM_H_

#include <vector>
#include <string>
#include "Searchable.h"

template<class T>
class MatrixProblem : public Searchable<T> {
  vector<vector<State<T> * >> m_vect;
  unsigned m_matrix_size;
  State<T> *m_initial;
  State<T> *m_goal;

 public:
  // constructor
  MatrixProblem(vector<vector<int>> *input, T initial, T goal) {
    this->m_vect = this->createMatrix(input);
    this->m_initial = new State<T>(&initial);
    this->m_goal = new State<T>(&goal);
  }

  State<T> getInitialState() override {
    return *(this->m_initial);
  }

  bool isGoalState(State<T> state) override {
    return state.equals(*this->m_goal);
  }

  list<State<T>*> getAllPossible(State<T> state) override {
    list<State<pair<int, int>>*> possibilities;
    unsigned boundary = this->m_matrix_size - 1, current_i = state.getMState()->first,
      current_j = state.getMState()->second;
    State<T> *neighbour = nullptr;

    // check up cell
    neighbour = this->m_vect[current_i - 1][current_j];
    if (current_i - 1 >= 0 && neighbour->getMCost() != -1) {
      pair<int, int> p(current_i - 1, current_j);
      auto *st = new State<pair<int,int>>(&p);
      possibilities.push_back(st);
    }

    // check down cell
    neighbour = this->m_vect[current_i + 1][current_j];
    if (current_i + 1 <= boundary && neighbour->getMCost() != -1) {
      pair<int, int> p(current_i + 1, current_j);
      possibilities.push_back(new State<T>(&p));
    }

    // check left cell
    neighbour = this->m_vect[current_i][current_j - 1];
    if (current_j - 1 >= 0 && neighbour->getMCost() != -1) {
      pair<int, int> p(current_i, current_j - 1);
      possibilities.push_back(new State<T>(&p));
    }

    // check right cell
    neighbour = this->m_vect[current_i][current_j + 1];
    if (current_j + 1 <= boundary && neighbour->getMCost() != -1) {
      pair<int, int> p(current_i, current_j + 1);
      possibilities.push_back(new State<T>(&p));
    }

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
        pair<int, int> new_p(i, j);
        auto *s = new State<pair<int, int>>(&new_p);
        int cost = (*input)[i][j];
        s->setMCost((double) cost);
        single_row.push_back(s);
      }
      matrix.push_back(single_row);
    }
    return matrix;
  }

 static string toString(string input) {
    size_t hashP = hash<string>{}(input);
    return to_string(hashP);
  }

  // END OF CLASS
};

#endif //GENERICSERVERSIDE__MATRIXPROBLEM_H_
