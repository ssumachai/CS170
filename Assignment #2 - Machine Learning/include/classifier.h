#ifndef __CLASSIFIER_H__
#define __CLASSIFIER_H__

#include "setup.h"
#include "dataset.h"

class dataset;

class classifier{
    private:
        std::vector<dataset*> datasets;
    public:
        // Constructors & Destructors
        classifier();
        ~classifier();

        // Train and Test Functions
        void parse();                                           // Also known as train()
        int test(int instance_index, std::vector<int> subsets); // Test function
        
        // Normalize Data required for Calculating Distance
        void normalizeData();

        // Distance Helper Function
        double getDistance(dataset* a, dataset* b, std::vector<int> features);

        // Getter Helper Functions
        double getDefaultRate();
        int getDataSize();
        int getFeatureSize();
        int getClassLabel(int i);

        // Void Helper Functions 
        void print();
        void subsetInput(std::vector<int> &f);
};

#endif