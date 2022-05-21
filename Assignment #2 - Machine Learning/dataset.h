#ifndef __DATASET_H__
#define __DATASET_H__

#include "problem.h"

class dataset{
    private:
        int classifier;
        int featureCount;
        std::vector<float> features;
    public:
        dataset();
        dataset(int type, std::vector<float> feats);
        ~dataset();

        int getInstance();
        int getFeatureCount();
        float getFeatureValue(int index);
        void setFeatureValue(int index, float value);
        void print();
};

#endif