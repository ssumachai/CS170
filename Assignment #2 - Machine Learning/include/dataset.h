#ifndef __DATASET_H__
#define __DATASET_H__

#include "problem.h"

class dataset{
    private:
        int classLabel;
        int featureCount;
        std::vector<float> features;
    public:
        // Constructors + Destructors
        dataset();
        dataset(int type, std::vector<float> feats);
        ~dataset();

        // Getter Helper Functions
        int getInstance();
        int getFeatureCount();
        float getFeatureValue(int index);

        // Setter Helper Function
        void setFeatureValue(int index, float value);
        
        // Void Helper Functions
        void print();
};

#endif