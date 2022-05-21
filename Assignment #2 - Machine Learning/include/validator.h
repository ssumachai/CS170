#ifndef __VALIDATOR_H__
#define __VALIDATOR_H__

#include "setup.h"
#include "classifier.h"

class validator{
    private:
        classifier* myClass;
    public:
        // Constructors + Destructors
        validator(classifier* c);
        ~validator();

        // Calculate and return Leave-One-Out-Validation
        double accuracy(std::vector<int> featureSubset);
};

#endif