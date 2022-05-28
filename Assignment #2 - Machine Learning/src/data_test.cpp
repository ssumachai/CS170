#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include "../include/classifier.h"
#include "../include/validator.h"

int main(){
   

    classifier* myClass = new classifier();

    std::cout << "Enter nearest neighbors to use: ";
    int buffer;

    std::cin >> buffer;

    validator* v = new validator(myClass, buffer);

    myClass->parse();

    myClass->print();

    myClass->normalizeData();

    myClass->print();

    double default_rate = myClass->getDefaultRate();

    std::cout << "Using no features and \"Default Rate\" evaluation, I get an accuracy of " << default_rate << "%\n";

    std::vector<int> featuresToTest = {};

    int set_to_use;

    std::cout << "Enter whether you want to test custom subset, or all [1/2]: ";

    std::cin >> set_to_use;

    switch(set_to_use){
        case 1:
            myClass->subsetInput(featuresToTest);
            break;
        case 2:
            for(int i = 0; i < 40; i++){
                featuresToTest.push_back(i);
            }
            break;
        default:
            break;
    }


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