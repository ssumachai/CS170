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
        double gDistance;           // g(n) = cost to get from node n from initial state
        int findBlankIndex();
        bool solutionfound();
        std::string direction;
        problem* moveUp();
        problem* moveDown();
        problem* moveLeft();
        problem* moveRight();
        int misplacedCost();
        int euclideanCost();
        void print();
        void queuesort(std::vector<problem*> &statequeue);
        void determineDirection(int value);
        std::vector<int> getCurrBoard();
};

struct MoveCost{
    bool operator()(problem* const b1, problem* const b2){
        if(b1->totalCost == b2->totalCost){
            if(b1->gDistance < b2->gDistance){
                return false;
            }
        }
        else{
            return b1->totalCost > b2->totalCost;
        }
    }
};

bool searchRepeats(problem* currentTile, const std::vector<problem*> repeats);

#endif