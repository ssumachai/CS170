#include "../include/setup.h"
#include "../include/problem.h"
#include "../include/validator.h"

int main(){
    int algorithm_to_use;
    double default_rate = 0.00;
    std::string algo_name = "";

    classifier* myClass = new classifier();

    setup(myClass, algorithm_to_use);

    validator* myValidator = new validator(myClass);

    std::cout << "This dataset has " << myClass->getFeatureSize() << " features (not including the class attribute, with ";
    std::cout << myClass->getDataSize() << " instances.\n\nPlease wait while I normalize the data...";

    myClass->normalizeData();

    // if forward selection and no features

    problem* myBoard = new problem(myClass, myValidator, algorithm_to_use);
    problem* solution = new problem();

    auto start = high_resolution_clock::now();

    switch(algorithm_to_use){
        case 1:
            algo_name = "Forward Selection";
            default_rate = myClass->getDefaultRate();

            std::cout << "Running nearest neighbor with no features (default rate), using \"leaving-one-out\" evaluation, I get an accuracy of ";
            std::cout << default_rate << "%\n";

            std::cout << "\nBeginning Search.\n\n";
            
            solution = ForwardSelection(myBoard);
            break;
        case 2:
            algo_name = "Backwards Elimination";
            default_rate = myValidator->accuracy(myBoard->getVector());
            std::cout << "Running nearest neighbor with all features (default rate), using \"leaving-one-out\" evaluation, I get a accuracy of ";
            std::cout << default_rate << "%\n";

            std::cout << "\nBeginning Search.\n\n";

            solution = BackwardElimination(myBoard);
            break;
        default:
            break;
    }

    auto end = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(end - start);

    std::cout << algo_name << " Search Completed, Total Time Elapsed: " << duration.count() << " ms.\n\n";

    solution->printSolution();
}