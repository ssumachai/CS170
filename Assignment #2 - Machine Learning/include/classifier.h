#ifndef __CLASSIFIER_H__
#define __CLASSIFIER_H__

#include "setup.h"
#include "dataset.h"

using namespace std::chrono;

class classifier{
    private:
        std::vector<dataset*> datasets;
    public:
        classifier();
        ~classifier();

        void parse();                   // Also known as train()
        int test(int instance_index, std::vector<int> subsets);   // Test function
        double getDefaultRate();
        void normalizeData();
        void print();
        int getDataSize();
        int getClassLabel(int i);
        double getDistance(dataset* a, dataset* b, std::vector<int> features);
        void subsetInput(std::vector<int> &f);
        int getFeatureSize();
};



#endif