#include "algorithms.h"
#include "problem.h"

int main(){
    int features, algorithm;
    double random_accuracy;

    setup(features, algorithm);

    problem* myBoard = new problem(features, algorithm);
    problem* solution = new problem();

    srand(time(NULL));
    
    switch(algorithm){
        case 1:
            random_accuracy = getRandomEval();
            std::cout << "Using no features and \"random\" evaluation, I get an accuracy of " << random_accuracy << "%\n";
            break;
        case 2:
            random_accuracy = getRandomEval();
            std::cout << "Using all features() {";
            for(int i = 1; i <= features; i++){
                if(i == features){
                    std::cout << i;
                }
                else{
                    std::cout << i << ",";
                }
            }
            std::cout << "}   and \"random\" evaluation, I got an accuracy of " << random_accuracy << "%\n";
    }
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

    solution->printSolution();
}