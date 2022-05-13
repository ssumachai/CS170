#ifndef __PROBLEM_H__
#define __PROBLEM_H__

#include "setup.h"

class problem{
    private:
        std::vector<int> feautures;
        double accuracy;
    public:
        problem();
        ~problem();

        //Helper Functions
        void print();
        double getAccuracy();
};

#endif