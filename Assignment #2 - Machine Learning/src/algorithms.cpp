#include "../include/algorithms.h"

double getRandomEval(){
    double temp = rand() % 1000;

    return temp / 10;
}

problem* ForwardSelection(problem* startBoard){
    std::priority_queue<problem*, std::vector<problem*>, sortAccu> children;
    if(startBoard->remainingSize() == 0){
        return startBoard;
    }
    for(int i = 0; i < startBoard->remainingSize(); i++){
        problem* temp = startBoard->generateForwardChild(i);
        temp->print();
        children.push(temp);
    }

    std::cout << "\n\n";
    
    if(children.top()->remainingSize() != 0)
        children.top()->printBest();

    return ForwardSelection(children.top());
}

problem* BackwardElimination(problem* startBoard){
    std::priority_queue<problem*, std::vector<problem*>, sortAccu> children;

    if(startBoard->frontierSize() == 0){
        return startBoard;
    }
    for(int i = 0; i < startBoard->frontierSize(); ++i){
        problem* temp = startBoard->generateBackwardsChild(i);
        temp->print();
        children.push(temp);
    }

    std::cout << "\n\n";

    if(children.top()->frontierSize() != 0){
        children.top()->printBest();
    }

    return BackwardElimination(children.top());
}