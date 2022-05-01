#include "problem.h"

bool checkSets(problem* move, std::set<std::vector<int>> explored, std::set<std::vector<int>> found){
    bool b1 = !(explored.find(move->getCurrBoard()) != explored.end());
    bool b2 = !(found.find(move->getCurrBoard()) != found.end());

    return b1 && b2;
}

//Here I will make the algorithm for each method
//UNIFORM COST SEARCH
problem* UNIFORMCOST(problem* initial_state, std::priority_queue<problem*, std::vector<problem*>, MoveCost> &statequeue, std::vector<problem*> &solutions, std::set<std::vector<int>> &repeats, int &maxsize, int &expanded){
    problem* root = initial_state;
    std::set<std::vector<int>> foundSet;

    std::cout << "Expanding state";
    root->print();

    statequeue.push(root);
    repeats.clear();

    if(root->solutionfound()){
        return root;
    }

    while(!statequeue.empty()){
        if(statequeue.size() > maxsize){
            maxsize = statequeue.size();
        }
        initial_state = statequeue.top();
        statequeue.pop();

        if(initial_state != NULL && (initial_state->solutionfound() && (initial_state->totalCost <= statequeue.top()->totalCost))){
            return initial_state;
        }

        repeats.insert(initial_state->getCurrBoard());
        
        std::vector<problem*> expansions;
        //EXPANSION
        ++expanded;
        expansions.push_back(initial_state->moveUp());
        expansions.push_back(initial_state->moveDown());
        expansions.push_back(initial_state->moveLeft());
        expansions.push_back(initial_state->moveRight());

        for(unsigned i = 0; i < 4; i++){
            if(expansions.at(i) != NULL){
                if(checkSets(expansions.at(i), repeats, foundSet)){
                    expansions.at(i)->determineDirection(i);
                    expansions.at(i)->parent = initial_state;
                    expansions.at(i)->totalCost = expansions.at(i)->gDistance;
                    statequeue.push(expansions.at(i));
                    foundSet.insert(expansions.at(i)->getCurrBoard());
                }
            }
        }
    }

    return NULL;
}

//A* WITH MISPLACED TILE HEURISTIC
problem* AMISPLACED(problem* initial_state, std::priority_queue<problem*, std::vector<problem*>, MoveCost> &statequeue, std::vector<problem*> &solutions, std::set<std::vector<int>> &repeats, int &maxsize, int &expanded){
    problem* root = initial_state;
    std::set<std::vector<int>> foundSet;

    std::cout << "Expanding state";
    root->print();

    statequeue.push(root);
    repeats.clear();

    if(root->solutionfound()){
        return root;
    }

    while(!statequeue.empty()){
        if(statequeue.size() > maxsize){
            maxsize = statequeue.size();
        }
        initial_state = statequeue.top();
        statequeue.pop();

        if(initial_state != NULL && (initial_state->solutionfound() && (initial_state->totalCost <= statequeue.top()->totalCost))){
            return initial_state;
        }

        repeats.insert(initial_state->getCurrBoard());
        
        std::vector<problem*> expansions;
        //EXPANSION
        ++expanded;
        expansions.push_back(initial_state->moveUp());
        expansions.push_back(initial_state->moveDown());
        expansions.push_back(initial_state->moveLeft());
        expansions.push_back(initial_state->moveRight());

        for(unsigned i = 0; i < 4; i++){
            if(expansions.at(i) != NULL){
                if(checkSets(expansions.at(i), repeats, foundSet)){
                    expansions.at(i)->determineDirection(i);
                    expansions.at(i)->heuristic = expansions.at(i)->misplacedCost();
                    expansions.at(i)->parent = initial_state;
                    expansions.at(i)->totalCost = expansions.at(i)->heuristic + expansions.at(i)->gDistance;
                    statequeue.push(expansions.at(i));
                    foundSet.insert(expansions.at(i)->getCurrBoard());
                }
            }
        }
    }

    return NULL;
}


//A* WITH EUCLIDEAN DISTANCE HEURISTIC   EUCLIDEAN == MANHATTAN
problem* AEUCLIDEAN(problem* initial_state, std::priority_queue<problem*, std::vector<problem*>, MoveCost> &statequeue, std::vector<problem*> &solutions, std::set<std::vector<int>> &repeats, int &maxsize, int &expanded){
    problem* root = initial_state;
    std::set<std::vector<int>> foundSet;

    std::cout << "Expanding state";
    root->print();

    statequeue.push(root);
    repeats.clear();

    if(root->solutionfound()){
        return root;
    }

    while(!statequeue.empty()){
        if(statequeue.size() > maxsize){
            maxsize = statequeue.size();
        }
        initial_state = statequeue.top();
        statequeue.pop();

        if(initial_state != NULL && (initial_state->solutionfound() && (initial_state->totalCost <= statequeue.top()->totalCost))){
            return initial_state;
        }

        repeats.insert(initial_state->getCurrBoard());
        
        std::vector<problem*> expansions;
        //EXPANSION
        ++expanded;
        expansions.push_back(initial_state->moveUp());
        expansions.push_back(initial_state->moveDown());
        expansions.push_back(initial_state->moveLeft());
        expansions.push_back(initial_state->moveRight());

        for(unsigned i = 0; i < 4; i++){
            if(expansions.at(i) != NULL){
                if(checkSets(expansions.at(i), repeats, foundSet)){
                    expansions.at(i)->determineDirection(i);
                    expansions.at(i)->heuristic = expansions.at(i)->euclideanCost();
                    expansions.at(i)->parent = initial_state;
                    expansions.at(i)->totalCost = expansions.at(i)->heuristic + expansions.at(i)->gDistance;
                    statequeue.push(expansions.at(i));
                    foundSet.insert(expansions.at(i)->getCurrBoard());
                }
            }
        }
    }

    return NULL;
}