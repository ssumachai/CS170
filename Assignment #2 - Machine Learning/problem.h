#ifndef __PROBLEM_H__
#define __PROBLEM_H__

#include "setup.h"
#include "algorithms.h"

class problem{
    private:
        std::vector<int> features;
        std::vector<int> remaining_features;
        problem* parent;
        double accuracy;
    public:
        problem();
        problem(int start);
        ~problem();

        //Generate Feature Children
        problem* generateChild(int index);

        //Print Functions
        void print();
        void printBest();
        void printSolution();

        //Helper + Getter Functions
        void fillFeatureBank(int index);
        double getAccuracy();
        std::vector<int> getVector();
        problem* getParent();
        int remainingSize();
};

struct sortAccu{
    bool operator()(problem* const b1, problem* const b2){
        return b1->getAccuracy() < b2->getAccuracy();
    }
};

#endif