#include "problem.h"
#include "solutionalgorithms.h"
using namespace std;

int main(){
    problem* currnode;
    std::vector<problem*> solutionpath; //it will be in reverse
    std::vector<int> problemB = {};
    std::vector<int> solution = {};
    
    int function_select = setup(solution, problemB);
    //tileBoard == initial state
    problem* tileBoard = new problem(problemB, number_rows, number_columns);
    std::vector<problem*> statequeue;
    std::vector<problem*> solutions;  
    //because A* doesn't stop after finding the first goal
    //so this will only be used for the A* searches
    statequeue.push_back(tileBoard);
    //this keeps track of the maxsize of the queue (YYY) on the project guide, it will start as 1
    int maxsize = statequeue.size(); 
    cout << "I got here";
    //this keeps track of the nodes expanded, doesn't have update implemented yet
    int nodesexpanded = 0; 

    //CALL THE SEARCH HERE
    
    switch(function_select){
        case 1:
            UNIFORMCOST(tileBoard, statequeue, solutions, maxsize);
            break;
        default:
            break;
    }

    cout << "I got to the end";

    //FOR THE EXPANDING OF THE NODES AND TRACING THE SEARCH, IT WILL BE PRINTED FROM
    //WITHIN THE SEARCH FUNCTIONS

    //AFTER THE SEARCH, DO THE MIN COST OF THE POSSIBLE SOLUTIONS AND GET THE BEST SOLUTION NODE
    queuesort(solutions);
    cout << "I can sort\n";
    currnode = solutions.at(0);
    cout << "I got the first solution\n";

    //this fills solution path with the reverse solutiion
    //ie 5 4 3 2 1, instead of 1 2 3 4 5
    while(currnode != NULL){
        solutionpath.push_back(currnode);
        currnode = currnode->parent;
    }

    //now print out the steps to get from the start state to the solution state
    cout << endl << endl << "SOLUTION PATH" << endl;
    solutionpath.back()->print();

    
    for(int i=solutionpath.size()-2; i>=0; --i){
        cout << endl << endl << "The best state to expand with g(n) = ";
        cout << solutionpath.at(i)->gDistance << " and h(n) = ";
        cout << solutionpath.at(i)->heuristic << " is..." << endl;
        cout << "Move " << solutionpath.at(i)->direction << endl;
        solutionpath.at(i)->print();
        if(i!=0){
            cout << "    Expanding this node...";
        }
        else{
            cout << endl << "    GOAL NODE REACHED" << endl << endl;
        }
    }

    cout << "To solve this problem the search algorithm expanded a total of " << nodesexpanded << " nodes." << endl;
    cout << "The maximum number of nodes in the queue at any one time: " << maxsize << "." << endl;
    cout << "The depth of the goal node was " << solutionpath.back()->gDistance << "." << endl;;

    //when i==0 it is at the solution statea2

    
    

    std::cout << "Misplaced Tiles: " << tileBoard->misplacedCost() << std::endl;   
    std::cout << "Manhattan Distance: " << tileBoard->euclideanCost() << std::endl;
}
© 2022 GitHub, Inc.
Terms
Privacy
Security
Status
Docs