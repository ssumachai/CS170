#include "problem.h"
#include "solutionalgorithms.h"

int main(){
    std::vector<int> test_case = {};
    problem* currnode;
    std::vector<problem*> solutionpath;

    int buf;
    bool test_select, algo_select = false;

    std::cout << "Welcome to Chai and Nikki's Test Case Solver!\nBoard preset is: 3 x 3\n";
    std::cout << "[1] - Trivial Board\n[2] - Very Easy Board\n[3] - Easy Board\n[4] - Doable Board\n[5] - Oh Boy Board\n[6] - Impossible Board\n";

    std::cout << "Please enter your selection (1 - 6): ";
    std::cin >> buf;

    while(!test_select){
        switch(buf){
            case 1:
                test_case = {1, 2, 3, 4, 5, 6, 7, 8, 0};
                test_select = true;
                break;
            case 2:
                test_case = {1, 2, 3, 4, 5, 6, 7, 0, 8};
                test_select = true;
                break;
            case 3:
                test_case = {1, 2, 0, 4, 5, 3, 7, 8, 6};
                test_select = true;
                break;
            case 4:
                test_case = {0, 1, 2, 4, 5, 3, 7, 8, 6};
                test_select = true;
                break;
            case 5:
                test_case = {8, 7, 1, 6, 0, 2, 5, 4, 3};
                test_select = true;
                break;
            case 6:
                test_case = {1, 2, 3, 4, 5, 6, 8, 7, 0};
                test_select = true;
                break;
            default:
                std::cout << "Invalid test case. Please try again: ";
                std::cin >> buf;
                break;
        }
    }

    problem* solutionFound;
    problem* tileBoard = new problem(test_case, 3, 3);
    std::priority_queue<problem*, std::vector<problem*>, MoveCost> statequeue;
    std::vector<problem*> solutions;
    std::set<std::vector<int>> repeatedstates;

    int maxsize = statequeue.size();
    int nodesexpanded = 1;

    std::cout << "1 -- Uniform Cost Search\n2 -- A* w/ Misplaced Tile\n3 -- A* w/ Euclidean Distance\n";
    std::cout << "Please enter your selection (1/2/3): ";
    std::cin >> buf;

    while(!algo_select){
               switch(buf){
            case 1:
                solutionFound = UNIFORMCOST(tileBoard, statequeue, solutions, repeatedstates, maxsize, nodesexpanded);
                algo_select = true;
                break;
            case 2:
                solutionFound = AMISPLACED(tileBoard, statequeue, solutions, repeatedstates, maxsize, nodesexpanded);
                algo_select = true;
                break;
            case 3:
                solutionFound = AEUCLIDEAN(tileBoard, statequeue, solutions, repeatedstates, maxsize, nodesexpanded);
                algo_select = true;
                break;
            default:
                std::cout << "Invalid Input, please try again: ";
                std::cin >> buf;
                break;
        } 
    }

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