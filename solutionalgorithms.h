#include "problem.h"
using namespace std;

void queuesort(std::vector<problem*> &statequeue){

    for(int i = 0; i<statequeue.size(); ++i){
        //reset the minindex & the minimum cost
        int minindex = i;
        int mincost = statequeue.at(i)->totalCost;

        for(int k = i; k<statequeue.size(); ++k){
            if(statequeue.at(k)->totalCost < mincost){
                mincost = statequeue.at(k)->totalCost;
                minindex = k;
            }
        }
        //swap the index with the current lowest min with the current index we are ordering
        problem* temp = statequeue.at(i);
        statequeue.at(i) = statequeue.at(minindex);
        statequeue.at(minindex) = temp;
    }
}

//Here I will make the algorithm for each method
//UNIFORM COST SEARCH
void UNIFORMCOST(problem* initial_state, std::vector<problem*> &statequeue, std::vector<problem*> &solutions, int &maxsize){

    if(statequeue.size() > maxsize){cout << "here tho"; maxsize = statequeue.size();}
    if(statequeue.empty()){
        return;
    }
    //WE WANT TO POP THE FRONT OF THE QUEUE    
    statequeue.erase(statequeue.begin());
    //uniform cost search returns at the first solution found
    if(initial_state->solutionfound() == true){
        solutions.push_back(initial_state);
        return;
    }


    //EXPANSION
    problem* new1 = initial_state->moveUp();
    problem* new2 = initial_state->moveDown();
    problem* new3 =initial_state->moveLeft();
    problem* new4 = initial_state->moveRight();

    if(new1 != NULL){
        new1->direction = "Up";
        ++new1->gDistance; 
        new1->parent = initial_state;
        new1->totalCost = new1->gDistance;
        statequeue.push_back(new1);
    }
    if(new2 != NULL){
        new2->direction = "Down";
        ++new2->gDistance; 
        new2->parent = initial_state;
        new2->totalCost = new2->gDistance;
        statequeue.push_back(new2);
    }
    if(new3 != NULL){
        new3->direction = "Left";
        ++new3->gDistance; 
        new3->parent = initial_state;
        new3->totalCost = new3->gDistance;
        statequeue.push_back(new3);
    }
    if(new4 != NULL){
        new4->direction = "Right";
        ++new4->gDistance; 
        new4->parent = initial_state;
        new4->totalCost = new4->gDistance;
        statequeue.push_back(new4);
    }

    queuesort(statequeue);

    //NEXT EXPANSION
    UNIFORMCOST(statequeue.at(0), statequeue, solutions, maxsize);
}


//A* WITH MISPLACED TILE HEURISTIC
void AMISPLACED(problem* initial_state, std::vector<problem*> &statequeue, std::vector<problem*> &solutions, int &maxsize){

    if(statequeue.size() > maxsize){maxsize = statequeue.size();}
    if(statequeue.empty()){
        return;
    }
    //WE WANT TO POP FRONT OF THE QUEUE
    statequeue.erase(statequeue.begin());
    //Check if frontier is solution, if so, add to list of possible solutions
    if(initial_state->solutionfound() == true){
        solutions.push_back(initial_state);
    }

    //EXPANSION
    problem* new1 = initial_state->moveUp();
    problem* new2 = initial_state->moveDown();
    problem* new3 =initial_state->moveLeft();
    problem* new4 = initial_state->moveRight();

    vector<problem*> validmovements;

    if(new1 != NULL){
        new1->direction = "Up";
        new1->heuristic = new1->misplacedCost();
        new1->parent = initial_state;
        ++new1->gDistance; 
        new1->totalCost = new1->heuristic + new1->gDistance;
        statequeue.push_back(new1);
    }
    if(new2 != NULL){
        new2->direction = "Down";
        new2->heuristic = new2->misplacedCost();
        new2->parent = initial_state;
        ++new2->gDistance; 
        new2->totalCost = new2->heuristic + new2->gDistance;
        statequeue.push_back(new2);
    }
    if(new3 != NULL){
        new3->direction = "Left";
        new3->heuristic = new3->misplacedCost();
        new3->parent = initial_state;
        ++new3->gDistance; 
        new3->totalCost = new3->heuristic + new3->gDistance;
        statequeue.push_back(new3);
    }
    if(new4 != NULL){
        new4->direction = "Right";
        new4->heuristic = new4->misplacedCost();
        new4->parent = initial_state;
        ++new4->gDistance; 
        new4->totalCost = new4->heuristic + new4->gDistance;
        statequeue.push_back(new4);
    }

    queuesort(statequeue);

    //NEXT EXPANSION
    AMISPLACED(statequeue.at(0), statequeue, solutions, maxsize);
}


//A* WITH EUCLIDEAN DISTANCE HEURISTIC   EUCLIDEAN == MANHATTAN
void AEUCLIDEAN(problem* initial_state, std::vector<problem*> &statequeue, vector<problem*> &solutions, int &maxsize){

    if(statequeue.size() > maxsize){maxsize = statequeue.size();}
    if(statequeue.empty()){
        return;
    }
    //WE WANT TO POP FRONT OF THE QUEUE
    statequeue.erase(statequeue.begin());
    //Check if frontier is solution, if so, add to list of possible solutions
    if(initial_state->solutionfound() == true){
      

    //EXPANSION
    problem* new1 = initial_state->moveUp();
    problem* new2 = initial_state->moveDown();
    problem* new3 =initial_state->moveLeft();
    problem* new4 = initial_state->moveRight();

    vector<problem*> validmovements;

    if(new1 != NULL){
        new1->direction = "Up";
        new1->heuristic = new1->euclideanCost();
        new1->parent = initial_state;
        ++new1->gDistance; 
        new1->totalCost = new1->heuristic + new1->gDistance;
        statequeue.push_back(new1);
    }
    if(new2 != NULL){
        new2-> direction = "Down";
        new2->heuristic = new2->euclideanCost();
        new2->parent = initial_state;
        ++new2->gDistance; 
        new2->totalCost = new2->heuristic + new2->gDistance;
        statequeue.push_back(new2);
    }
    if(new3 != NULL){
        new3->direction = "Left";
        new3->heuristic = new3->euclideanCost();
        new3->parent = initial_state;
        ++new3->gDistance; 
        new3->totalCost = new3->heuristic + new3->gDistance;
        statequeue.push_back(new3);
    }
    if(new4 != NULL){
        new4->direction = "Right";
        new4->heuristic = new4->euclideanCost();
        new4->parent = initial_state;
        ++new4->gDistance; 
        new4->totalCost = new4->heuristic + new4->gDistance;
        statequeue.push_back(new4);
    }

    queuesort(statequeue);

    //NEXT EXPANSION
    AEUCLIDEAN(statequeue.at(0), statequeue, solutions, maxsize);
}
}