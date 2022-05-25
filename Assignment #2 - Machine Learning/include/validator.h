#ifndef __VALIDATOR_H__
#define __VALIDATOR_H__

#include "setup.h"
#include "classifier.h"

class classifier;

class validator{
    private:
        classifier* myClass;
        int k_neighbors;
    public:
        // Constructors + Destructors
        validator(classifier* c, int k);
        ~validator();

        // Calculate and return Leave-One-Out-Validation
        double accuracy(std::vector<int> featureSubset);
};

#endif