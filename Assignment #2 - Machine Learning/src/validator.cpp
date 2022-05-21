#include "../include/validator.h"

validator::validator(classifier* c){
    myClass = c;
}

double validator::accuracy(std::vector<int> featureSubset){
    int correct = 0;
    int result = 0;
    double percentage = 0;

    auto start = high_resolution_clock::now();

    for(int i = 0; i < myClass->getDataSize(); i++){
        result = myClass->test(i, featureSubset);
        if(result == myClass->getClassLabel(i)){
            correct++;
        }
    }

    auto stop = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(stop - start);

    std::cout << "Leave-One-Out-Validator took " << duration.count() << " ms.\n";

    percentage = (double)correct / (double)myClass->getDataSize();

    return percentage;
}