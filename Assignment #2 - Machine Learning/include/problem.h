#ifndef __PROBLEM_H__
#define __PROBLEM_H__

#include "setup.h"
#include "algorithms.h"
#include "classifier.h"
#include "validator.h"

class classifier;
class validator;

class problem{
    private:
        classifier* problem_set;
        validator* tester;
        std::vector<int> features;
        std::vector<int> remaining_features;
        problem* parent;
        double accuracy;
    public:
        problem();
        problem(classifier* c, validator* v, int algo_select);
        ~problem();

        //Generate Feature Children
        problem* generateForwardChild(int index);
        problem* generateBackwardsChild(int index);
        problem* getBestSubset();

        bool checkDuplicates();

        //Print Functions
        void print();
        void printBest();
        void printSolution(double initial_accuracy);

        //Helper + Getter Functions
        void fillFeatureBank(int index, int select);
        double getAccuracy();
        std::vector<int> getVector();
        problem* getParent();
        int remainingSize();
        int frontierSize();
};

struct sortAccu{
    bool operator()(problem* const b1, problem* const b2){
        return b1->getAccuracy() < b2->getAccuracy();
    }
};

#endif