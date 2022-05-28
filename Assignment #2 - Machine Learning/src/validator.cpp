#include "../include/validator.h"

validator::validator(classifier* c, int k){
    myClass = c;
    k_neighbors = k;
}

double validator::accuracy(std::vector<int> featureSubset){
    int correct = 0;
    int result = 0;
    double percentage = 0;

    for(int i = 0; i < myClass->getDataSize(); i++){
        result = myClass->test(i, k_neighbors, featureSubset);
        if(result == myClass->getClassLabel(i)){
            correct++;
        }
    }

    percentage = (double)correct / (double)myClass->getDataSize();

    return percentage;
}