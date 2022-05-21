#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include "../include/classifier.h"
#include "../include/validator.h"

int main(){
   

    classifier* myClass = new classifier();
    validator* v = new validator(myClass);

    myClass->parse();

    myClass->normalizeData();

    double default_rate = myClass->getDefaultRate();

    std::cout << "Using no features and \"Default Rate\" evaluation, I get an accuracy of " << default_rate << "%\n";

    std::vector<int> featuresToTest = {};

    myClass->subsetInput(featuresToTest);

    double subsetAccuracy = v->accuracy(featuresToTest);

    std::cout << "If you only use feature(s) {";
    for(int i = 0; i < featuresToTest.size(); i++){
        if(i == featuresToTest.size() - 1){
            std::cout << featuresToTest[i] + 1;
        }
        else{
            std::cout << featuresToTest[i] + 1 << ", ";
        }
    }
    std::cout << "}, accuracy should be about " << subsetAccuracy;

    return 0;
}