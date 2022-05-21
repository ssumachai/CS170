#include "../include/problem.h"

problem::problem(){
    features = {};
    accuracy = 0.00;
    remaining_features = {};
    parent = NULL;
}
problem::problem(int start, int choose){
    features = {};
    accuracy = 0.00;
    fillFeatureBank(start, choose);
    parent = NULL;
}

problem* problem::generateForwardChild(int index){
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

problem* problem::generateBackwardsChild(int index){
    problem* temp = new problem();
    std::vector<int> temp_rem = getVector();
    temp_rem.erase(temp_rem.begin() + index);
    temp->features = temp_rem;
    temp->accuracy = getRandomEval();
    temp->remaining_features = this->remaining_features;
    temp->parent = this;

    return temp;
}

problem* problem::getBestSubset(){
    problem* temp = new problem();
    temp = this;
    problem* max = new problem();
    max = this;
    while(temp != NULL){
        if(temp->accuracy > max->accuracy){
            max = temp;
        }
        temp = temp->parent;
    }

    return max;
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

void problem::printSolution(double initial_accuracy){
    problem* printThis = getBestSubset();
    
    if(printThis->accuracy < initial_accuracy){
        std::cout << "(Warning, Accuracy has decreased!)\n";
    }
    
    std::cout << "Finished Search!! The best feature subset is {";
    
    for(int i = printThis->features.size() - 1; i >= 0; i--){
        if(i == 0){
            std::cout << printThis->features[i];
        }
        else{
            std::cout << printThis->features[i] << ",";
        }
    }

    std::cout << "}, which has an accuracy of " << printThis->accuracy << "%\n";

}

void problem::fillFeatureBank(int index, int select){
    for(unsigned i = 1; i <= index; i++){
        if(select == 1){
            remaining_features.push_back(i);
        }
        else{
            features.push_back(i);
        }
    }
}

double problem::getAccuracy(){
    return this->accuracy;
}

problem* problem::getParent(){
    return this->parent;
}

int problem::frontierSize(){
    return (int)features.size();
}

int problem::remainingSize(){
    return (int)remaining_features.size();
}