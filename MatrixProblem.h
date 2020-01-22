//
// Created by yuval on 15/01/2020.
//

#ifndef GENERICSERVERSIDE__MATRIXPROBLEM_H_
#define GENERICSERVERSIDE__MATRIXPROBLEM_H_

#include <vector>
#include <string>
#include <climits>
#include "Searchable.h"
#include <list>
extern int lalala;
template<class T>
class MatrixProblem : public Searchable<T> {
  vector<vector<State<T> * >> m_vect;
  unsigned m_matrix_size;
  State<T> *m_initial;
  State<T> *m_goal;

 public:
  // constructor
  MatrixProblem(vector<vector<int>> *input, T *initial, T *goal) {
    this->m_vect = this->createMatrix(input, initial, goal);
    this->m_initial = new State<T>(initial);
    double value = 0;
    vector<vector<int>> temp = *input;
    value = temp[initial->first][initial->second];
    this->m_initial->setMCost(value);
    this->m_initial->setSumCost(value);

    this->m_goal = new State<T>(goal);
    value = temp[goal->first][goal->second];
    this->m_goal->setMCost(value);
    this->m_goal->setSumCost(value);
  }

  State<T> getInitialState() override {
    return *(this->m_initial);
  }

  bool isGoalState(State<T> state) override {
    return state.equals(*this->m_goal);
  }

  string getDirection(State<T> a, State<T> b) {
    // get positions
    int a_i = a.getMState()->first, a_j = a.getMState()->second;
    int b_i = b.getMState()->first, b_j = b.getMState()->second;

    if (b_i == a_i) {
      if (b_j < a_j) {
        return "LEFT";
      } else {
        return "RIGHT";
      }
    } else if (b_j == a_j) {
      if (b_i < a_i) {
        return "UP";
      } else {
        return "DOWN";
      }
    }
    throw "COULD NOT RESOLVE DIRECTION";

  }

  string resolve(State<T> *goal) override {
    list<State<T>> path;
    string path_str;
    path.push_front(*goal);
    while (goal->getMCameFrom() != nullptr) {
      path.push_front(*goal->getMCameFrom());
      goal = goal->getMCameFrom();
    }

    for (auto itr = path.begin(); next(itr) != path.end(); itr++) {
      try {
        // get the direction between current two states
        path_str.append(getDirection(*itr, *next(itr)) + " ");
        // get the current cost
        path_str.append("(" + to_string((int) next(itr)->getSumCost()) + ")" + " ");
      } catch (const char *c) {
        cerr << c << endl;
      }
    }
    return path_str;

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
        st->setSumCost(neighbour->getSumCost());
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
        st->setSumCost(neighbour->getSumCost());
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
        st->setSumCost(neighbour->getSumCost());
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
        st->setSumCost(neighbour->getSumCost());
        possibilities.push_back(st);
      }
    }
    return possibilities;
  }

  vector<vector<State<pair<int, int>> * >> createMatrix(vector<vector<int>> *input, T *initial, T *goal) {
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
        s->setSumCost((double) cost);
        // check if this state is initial or goal
        if (*(s->getMState()) == *initial) {
          this->m_initial = s;
        } else if (*(s->getMState()) == *goal) {
          this->m_goal = s;
        }
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

  State<T> getGoal() override {
    return *(this->m_goal);
  }

  // END OF CLASS
};

#endif //GENERICSERVERSIDE__MATRIXPROBLEM_H_
