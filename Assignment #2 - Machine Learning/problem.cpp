#include "problem.h"

problem::problem(){
    features = {};
    accuracy = 0.00;
    remaining_features = {};
    parent = NULL;
}
problem::problem(int start){
    features = {};
    accuracy = 0.00;
    fillFeatureBank(start);
    parent = NULL;
}

problem* problem::generateChild(int index){
    problem* temp = new problem();
    temp->features = getVector();
    temp->features.push_back(remaining_features.at(index));
    temp->accuracy = getRandomEval();
    
    std::vector<int> temp_rem = this->remaining_features;

    temp_rem.erase(temp_rem.begin() + index);

    temp->remaining_features = temp_rem;
    temp->parent = this;

    return temp;
}

void problem::print(){
    std::cout << "Using features() {";

    for(int i = features.size() - 1; i >= 0; i--){
        if(i == 0){
            std::cout << features[i];
        }
        else{
            std::cout << features[i] << ",";
        }
    }

    std::cout << "} accuracy is " << accuracy << "%\n";
}

std::vector<int> problem::getVector(){
    return this->features;
}

void problem::printBest(){
    std::cout << "Feature set {";
    
    for(int i = features.size() - 1; i >= 0; i--){
        if(i == 0){
            std::cout << features[i];
        }
        else{
            std::cout << features[i] << ",";
        }
    }

    std::cout << "} was best, accuracy is " << accuracy << "%\n\n\n";    
}

void problem::printSolution(){
    std::cout << "(Warning, Accuracy has decreased!)\nFinished Search!! The best feature subset is {";

    for(int i = features.size() - 1; i >= 0; i--){
        if(i == 0){
            std::cout << features[i];
        }
        else{
            std::cout << features[i] << ",";
        }
    }

    std::cout << "}, which has an accuracy of " << accuracy << "%\n";

}

void problem::fillFeatureBank(int index){
    for(unsigned i = 1; i <= index; i++){
        remaining_features.push_back(i);
    }
}

double problem::getAccuracy(){
    return this->accuracy;
}

problem* problem::getParent(){
    return this->parent;
}

int problem::remainingSize(){
    return (int)remaining_features.size();
}