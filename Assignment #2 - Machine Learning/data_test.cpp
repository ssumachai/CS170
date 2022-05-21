#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include "classifier.h"

int main(){
   

    classifier* myClass = new classifier();

    myClass->parse();

    myClass->normalizeData();

    double default_rate = myClass->getDefaultRate();

    std::cout << "Using no features and \"Default Rate\" evaluation, I get an accuracy of " << default_rate << "%\n";

    return 0;
}