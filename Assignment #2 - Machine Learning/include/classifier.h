#ifndef __CLASSIFIER_H__
#define __CLASSIFIER_H__

#include "setup.h"
#include "dataset.h"

class dataset;

struct NearestNode{
    int index;
    double distance;

    // constructor
    NearestNode(int i, double d): index(i), distance(d) {}
    bool operator<(const NearestNode &r) const {
        return distance < r.distance;
    }
};

class classifier{
    private:
        std::vector<dataset*> datasets;
    public:
        // Constructors & Destructors
        classifier();
        ~classifier();

        // Train and Test Functions
        void parse();                                                           // Also known as train()
        int test(int instance_index, int k_nearest, std::vector<int> subsets);  // Test function
        
        // Normalize Data required for Calculating Distance
        void normalizeData();

        // Distance Helper Function
        double getDistance(dataset* a, dataset* b, std::vector<int> features);

        // Utility Sorter Function for K Nearest Neighbors
        void sort_cut(std::vector<NearestNode> &d);

        // Helper Function to Check Nearest Neighbors
        int evaluateNeighbors(std::vector<NearestNode> d);

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