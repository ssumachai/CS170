#include "dataset.h"

dataset::dataset(){
    classifier = 0;
    featureCount = 0;
    features = {};
}

dataset::dataset(int type, std::vector<float> feats){
    classifier = type;
    featureCount = feats.size();
    features = feats;
}

float dataset::getFeatureValue(int index){
    return features[index];
}

void dataset::print(){
    std::cout << classifier << "\t";
    for(int i = 0; i < featureCount; i++){
        std::cout << features[i] << "\t";
    }
}
