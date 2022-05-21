#ifndef __CLASSIFIER_H__
#define __CLASSIFIER_H__

#include <fstream>
#include <math.h>
#include <chrono>
#include "dataset.h"

using namespace std::chrono;

class classifier{
    private:
        std::vector<dataset*> datasets;
    public:
        classifier();
        ~classifier();

        void parse();                   // Also known as train()
        int test(int instance_index);   // Test function
        double getDefaultRate();
        void normalizeData();
        void print();
};

#endif