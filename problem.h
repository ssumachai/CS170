#ifndef __PROBLEM_H__
#define __PROBLEM_H__

#include "setup.h"

class problem{
    private:
        std::vector<int> currBoard;
        std::vector<int> goalBoard;
        int num_rows;
        int num_columns;
        int boardSize;
    public:
        problem();
        problem(std::vector<int> v, int rows, int columns);
        ~problem();
        problem* parent;
        double totalCost;           // f(n) = g(n) + h(n)
        double heuristic;           // h(n) = estimated distance from n to the goal
        double gDistance;            // g(n) = cost to get from node n from initial state
        problem* moveUp();
        problem* moveDown();
        problem* moveLeft();
        problem* moveRight();
        int misplacedCost();
        int euclideanCost();

};

#endif