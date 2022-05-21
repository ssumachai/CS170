#include "../include/problem.h"
#include "../include/solutionalgorithms.h"

int main(){
    problem* currnode;
    std::vector<problem*> solutionpath; //it will be in reverse
    std::vector<int> problemB = {};
    std::vector<int> solution = {};
    
    int function_select = setup(solution, problemB);
    //tileBoard == initial state
    problem* tileBoard = new problem(problemB, number_rows, number_columns);
    std::priority_queue<problem*, std::vector<problem*>, MoveCost> statequeue;
    std::vector<problem*> solutions;  
    std::set<std::vector<int>> repeatedstates;
    //because A* doesn't stop after finding the first goal
    //so this will only be used for the A* searches
    statequeue.push(tileBoard);
    repeatedstates.insert(tileBoard->getCurrBoard());
    //this keeps track of the maxsize of the queue (YYY) on the project guide, it will start as 1
    int maxsize = statequeue.size(); 
    //this keeps track of the nodes expanded, doesn't have update implemented yet
    int nodesexpanded = 1; 

    //CALL THE SEARCH HERE
    
    problem* solutionFound;

    switch(function_select){
        case 1:
            solutionFound = UNIFORMCOST(tileBoard, statequeue, solutions, repeatedstates, maxsize, nodesexpanded);
            break;
        case 2:
            solutionFound = AMISPLACED(tileBoard, statequeue, solutions, repeatedstates, maxsize, nodesexpanded);
            break;
        case 3:
            solutionFound = AEUCLIDEAN(tileBoard, statequeue, solutions, repeatedstates, maxsize, nodesexpanded);
            break;
        default:
            break;
    }

    //FOR THE EXPANDING OF THE NODES AND TRACING THE SEARCH, IT WILL BE PRINTED FROM
    //WITHIN THE SEARCH FUNCTIONS

    //AFTER THE SEARCH, DO THE MIN COST OF THE POSSIBLE SOLUTIONS AND GET THE BEST SOLUTION NODE
     if(solutionFound != NULL){
        currnode = solutionFound;
        
        //this fills solution path with the reverse solutiion
        //ie 5 4 3 2 1, instead of 1 2 3 4 5
        while(currnode != NULL){
            solutionpath.push_back(currnode);
            currnode = currnode->parent;
        }

        //now print out the steps to get from the start state to the solution state
        std::cout << "\n\nSOLUTION PATH\n";
        solutionpath.back()->print();

        
        for(int i=solutionpath.size()-2; i>=0; --i){
            std::cout << "\n\nThe best state to expand with g(n) = ";
            std::cout << solutionpath.at(i)->gDistance << " and h(n) = ";
            std::cout << solutionpath.at(i)->heuristic << " is...\n";
            std::cout << "Move " << solutionpath.at(i)->direction << std::endl;
            solutionpath.at(i)->print();
            if(i!=0){
                std::cout << "    Expanding this node...";
            }
            else{
                std::cout << "\n    GOAL NODE REACHED\n\n";
            }
        }

        std::cout << "To solve this problem the search algorithm expanded a total of " << nodesexpanded << " nodes.\n";
        std::cout << "The maximum number of nodes in the queue at any one time: " << maxsize << ".\n";
        std::cout << "The depth of the goal node was " << solutionpath.front()->gDistance << ".\n";

        //when i==0 it is at the solution statea2
    }
    else{
        std::cout << "No Solution Found! GG!\n";
    }
}