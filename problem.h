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
        // Constructors and Destructor
        problem();
        problem(std::vector<int> v, int rows, int columns);
        ~problem();

        //Public Member Variables Accessed by Program
        problem* parent;
        double totalCost;           // f(n) = g(n) + h(n)
        double heuristic;           // h(n) = estimated distance from n to the goal
        double gDistance;           // g(n) = cost to get from node n from initial state
        std::string direction;

        // Move Functions, returns a Problem Pointer
        problem* moveUp();
        problem* moveDown();
        problem* moveLeft();
        problem* moveRight();

        // Heuristic Calculation Functions
        int misplacedCost();
        int euclideanCost();

        // Helper Functions
        void print();
        void determineDirection(int value);
        std::vector<int> getCurrBoard();
        int findBlankIndex();
        bool solutionfound();
};

// Structure for Priority Queue sorting

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

#endif