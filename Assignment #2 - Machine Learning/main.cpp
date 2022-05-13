#include "algorithms.h"

int main(){
    int features, algorithm;
    double random_accuracy;

    setup(features, algorithm);

    srand(time(NULL));
    
    random_accuracy = getRandomEval();
    std::cout << "Using no features and \"random\" evaluation, I get an accuracy of " << random_accuracy << "%\n";

    std::cout << features << std::endl << algorithm << std::endl;
}