#include <iostream>
#include <fstream>
#include <string>
#include "dataset.h"

void parse(std::vector<dataset*> &toParse, int dataindex){
    std::string fileName;
    int dataSize;
    int classType;
    std::vector<float> features = {};
    
    switch(dataindex){
        case 1:
            fileName = "baby_dataset.txt";
            dataSize = 3;
            break;
        default:
            break;
    }

    std::ifstream infile;
    infile.open(fileName);
    float buffer;

    while(infile >> buffer){
        classType = buffer;
        for(int i = 0; i < dataSize; i++){
            infile >> buffer;
            features.push_back(buffer);
        }
        dataset* temp = new dataset(classType, features);
        toParse.push_back(temp);
        features.clear();
    }

    infile.close();
}


int main(){
    std::vector<dataset*> myData = {};
    parse(myData, 1);

    for(int i = 0; i < myData.size(); i++){
        myData[i]->print();
        std::cout << std::endl;
    }

    return 0;
}