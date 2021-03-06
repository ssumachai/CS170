#include "../include/algorithms.h"
#include "../include/problem.h"

int main(){
    int features, algorithm;
    double random_accuracy;

    setup(features, algorithm);

    problem* myBoard = new problem(features, algorithm);
    problem* solution = new problem();

    srand(time(NULL));
    
    random_accuracy = getRandomEval();
    std::cout << "Using no features and \"random\" evaluation, I get an accuracy of " << random_accuracy << "%\n";
    
    std::cout << "\nBeginning search.\n\n";

    switch(algorithm){
        case 1:
            solution = ForwardSelection(myBoard);
            break;
        case 2:
            solution = BackwardElimination(myBoard);
            break;
        default:
            break;
    }

    solution->printSolution(random_accuracy);
}