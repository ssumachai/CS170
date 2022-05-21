#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include "dataset.h"
#

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
        case 2:
            fileName = "small_dataset.txt";
            dataSize = 10;
            break;
        case 3:
            fileName = "large_dataset.txt";
            dataSize = 40;
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

double getDefaultRate(const std::vector<dataset*> toParse){
    double instance_one, instance_two, total = 0;

    for(unsigned i = 0; i < toParse.size(); i++){
        if(toParse.at(i)->getInstance() == 1){
            instance_one++;
        }
        else{
            instance_two++;
        }
        total++;
    }

    if(instance_one > instance_two){
        return instance_one / total;
    }
    else{
        return instance_two / total;
    }
}

void normalizeData(std::vector<dataset*> &v){
    double mean;
    double total;
    double sd;
    
    for(int i = 0; i < v[0]->getFeatureCount(); i++){
        mean = total = sd = 0;
        for(int j = 0; j < v.size(); j++){
            total += v[j]->getFeatureValue(i);
        }

        mean = total / v.size();

        for(int k = 0; k < v.size(); k++){
            sd += pow(v[k]->getFeatureValue(i) - mean, 2);
        }

        sd = sd / (v.size() - 1);

        sd = sqrt(sd);

        for(int l = 0; l < v.size(); l++){
            float temp = (v[l]->getFeatureValue(i) - mean) / sd;
            v[l]->setFeatureValue(i, temp);
        }
    }
}


int main(){
    std::vector<dataset*> myData = {};
    int setBuffer;
    
    std::cout << "Select a dataset to use:\n[1] - Baby Set (5 Instances, 3 Features\n[2] - Small Set (100 Instances, 10 Features)\n[3] - Large Set (1000 Instances, 40 Features)\n";
    std::cin >> setBuffer;    

    parse(myData, setBuffer);

    std::cout << "Pre-Normalization Data\n";

    for(int i = 0; i < myData.size(); i++){
        myData[i]->print();
        std::cout << std::endl;
    }

    normalizeData(myData);

    std::cout << "Post-Normalization Data\n";

    for(int i = 0; i < myData.size(); i++){
        myData[i]->print();
        std::cout << std::endl;
    }

    std::cout << "Using no features and \"Default Rate\" evaluation, I get an accuracy of " << getDefaultRate(myData) << "%\n";

    return 0;
}