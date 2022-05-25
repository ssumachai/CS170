#include "../include/problem.h"

problem::problem(){
    features = {};
    accuracy = 0.00;
    remaining_features = {};
    parent = NULL;
    accuracy_decreased = false;
}

problem::problem(classifier* c, validator* v, int algo_select){
    problem_set = c;
    tester = v;
    features = {};
    accuracy = c->getDefaultRate();
    fillFeatureBank(c->getFeatureSize(), algo_select);
    parent = NULL;
    accuracy_decreased = false;
}

problem* problem::generateForwardChild(int index){
    problem* temp = new problem();
    temp->problem_set = this->problem_set;
    temp->tester = this->tester;
    temp->features = getVector();
    temp->features.push_back(remaining_features.at(index));
    temp->accuracy = tester->accuracy(temp->features);
    
    std::vector<int> temp_rem = this->remaining_features;

    temp_rem.erase(temp_rem.begin() + index);

    temp->remaining_features = temp_rem;
    temp->parent = this;

    if(parent != NULL){
        if(parent->accuracy > temp->accuracy){
            accuracy_decreased = true;
        }
    }

    return temp;
}

problem* problem::generateBackwardsChild(int index){
    problem* temp = new problem();
    temp->problem_set = this->problem_set;
    temp->tester = this->tester;
    std::vector<int> temp_rem = getVector();
    temp_rem.erase(temp_rem.begin() + index);
    temp->features = temp_rem;
    temp->accuracy = tester->accuracy(temp->features);
    temp->remaining_features = this->remaining_features;
    temp->parent = this;

    if(parent != NULL){
        if(parent->accuracy > temp->accuracy){
            accuracy_decreased = true;
        }
    }

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
            std::cout << features[i] + 1;
        }
        else{
            std::cout << features[i] + 1 << ",";
        }
    }

    std::cout << "} accuracy is " << accuracy << "%\n";
}

std::vector<int> problem::getVector(){
    return this->features;
}

void problem::printBest(){
    if(accuracy_decreased){
        std::cout << "(Warning, Accuracy has decreased!! Continuing search in case of local maxima)\n";
    }
    
    std::cout << "Feature set {";
    
    for(int i = features.size() - 1; i >= 0; i--){
        if(i == 0){
            std::cout << features[i] + 1;
        }
        else{
            std::cout << features[i] + 1 << ",";
        }
    }

    std::cout << "} was best, accuracy is " << accuracy << "%\n\n\n";    
}

void problem::printSolution(){
    problem* printThis = getBestSubset();
    
    std::cout << "Finished Search!! The best feature subset is {";
    
    for(int i = printThis->features.size() - 1; i >= 0; i--){
        if(i == 0){
            std::cout << printThis->features[i] + 1;
        }
        else{
            std::cout << printThis->features[i] + 1 << ",";
        }
    }

    std::cout << "}, which has an accuracy of " << printThis->accuracy << "%\n";

}

void problem::fillFeatureBank(int index, int select){
    for(unsigned i = 0; i < index; i++){
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