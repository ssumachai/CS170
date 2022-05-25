#include "../include/setup.h"
#include "../include/problem.h"
#include "../include/validator.h"

int main(){
    int algorithm_to_use;
    double default_rate = 0.00;

    classifier* myClass = new classifier();

    setup(myClass, algorithm_to_use);

    validator* myValidator = new validator(myClass);

    std::cout << "This dataset has " << myClass->getFeatureSize() << " features (not including the class attribute, with ";
    std::cout << myClass->getDataSize() << " instances.\nPlease wait while I normalize the data...";

    myClass->normalizeData();

    std::cout << "\tDone!\n";

    // if forward selection and no features

    problem* myBoard = new problem(myClass, myValidator, algorithm_to_use);
    problem* solution = new problem();

    switch(algorithm_to_use){
        case 1:
            default_rate = myClass->getDefaultRate();

            std::cout << "Running nearest neighbor with no features (default rate), using \"leaving-one-out\" evaluation, I get an accuracy of ";
            std::cout << default_rate << "%\n";

            std::cout << "\nBeginning Search.\n";

            solution = ForwardSelection(myBoard);
            break;
        case 2:
            default_rate = myValidator->accuracy(myBoard->getVector());
            std::cout << "Running nearest neighbor with all features (default rate), using \"leaving-one-out\" evaluatiom, I get a accuracy of ";
            std::cout << default_rate << "%\n";

            std::cout << "\nBeginning Search.\n";

            solution = BackwardElimination(myBoard);
            break;
        default:
            break;
    }

    solution->printSolution(default_rate);
}