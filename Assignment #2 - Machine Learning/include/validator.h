#ifndef __VALIDATOR_H__
#define __VALIDATOR_H__

#include "setup.h"
#include "classifier.h"

class validator{
    private:
        classifier* myClass;
    public:
        validator(classifier* c);
        ~validator();
        double accuracy(std::vector<int> featureSubset);
};

#endif