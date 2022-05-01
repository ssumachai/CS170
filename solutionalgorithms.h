#include "problem.h"
using namespace std;

/*void queuesort(std::vector<problem*> &statequeue){
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
*/

bool checkSets(problem* move, std::set<vector<int>> explored, std::set<vector<int>> found){
    bool b1 = !(explored.find(move->getCurrBoard()) != explored.end());
    bool b2 = !(found.find(move->getCurrBoard()) != found.end());

    return b1 && b2;
}

//Here I will make the algorithm for each method
//UNIFORM COST SEARCH
problem* UNIFORMCOST(problem* initial_state, std::priority_queue<problem*, vector<problem*>, MoveCost> &statequeue, std::vector<problem*> &solutions, std::set<vector<int>> &repeats, int &maxsize, int &expanded){
    problem* root = initial_state;
    problem* goalNode = NULL;
    std::set<vector<int>> foundSet;

    std::cout << "Expanding state";
    root->print();

    statequeue.push(root);

    if(root->solutionfound()){
        return root;
    }

    while(!statequeue.empty()){
        if(statequeue.size() > maxsize){
            maxsize = statequeue.size();
        }
        initial_state = statequeue.top();
        if(initial_state->gDistance != 0){
            //std::cout << "The best state to expand with g(n) = " << initial_state->gDistance << " and h(n) = " << initial_state->heuristic << "is ...\n";
            //initial_state->print(); 
        }
        statequeue.pop();

        if(goalNode != NULL && (goalNode->solutionfound() && (goalNode->totalCost <= statequeue.top()->totalCost))){
            return goalNode;
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
                    if(expansions.at(i)->solutionfound()){
                        goalNode = expansions.at(i);
                    } 

                }
            }
        }
    }

    return NULL;
    //NEXT EXPANSION
    /*cout << "The best state to expand with g(n) = " << statequeue.at(0)->gDistance << " and h(n) = " << statequeue.at(0)->heuristic << " is..." << endl;
    statequeue.at(0)->print();
    cout << "   Expanding this node..." << endl << endl;
    */
}

//A* WITH MISPLACED TILE HEURISTIC
problem* AMISPLACED(problem* initial_state, std::priority_queue<problem*, vector<problem*>, MoveCost> &statequeue, std::vector<problem*> &solutions, std::set<vector<int>> &repeats, int &maxsize, int &expanded){
    problem* root = initial_state;
    problem* goalNode = NULL;
    std::set<vector<int>> foundSet;

    std::cout << "Expanding state";
    root->print();

    statequeue.push(root);

    if(root->solutionfound()){
        return root;
    }

    while(!statequeue.empty()){
        if(statequeue.size() > maxsize){
            maxsize = statequeue.size();
        }
        initial_state = statequeue.top();
        if(initial_state->gDistance != 0){
            //std::cout << "The best state to expand with g(n) = " << initial_state->gDistance << " and h(n) = " << initial_state->heuristic << "is ...\n";
            //initial_state->print(); 
        }
        statequeue.pop();

        if(goalNode != NULL && (goalNode->solutionfound() && (goalNode->totalCost <= statequeue.top()->totalCost))){
            return goalNode;
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
                    if(expansions.at(i)->solutionfound()){
                        goalNode = expansions.at(i);
                    } 

                }
            }
        }
    }

    return NULL;
    //NEXT EXPANSION
    /*cout << "The best state to expand with g(n) = " << statequeue.at(0)->gDistance << " and h(n) = " << statequeue.at(0)->heuristic << " is..." << endl;
    statequeue.at(0)->print();
    cout << "   Expanding this node..." << endl << endl;
    */
}


//A* WITH EUCLIDEAN DISTANCE HEURISTIC   EUCLIDEAN == MANHATTAN
problem* AEUCLIDEAN(problem* initial_state, std::priority_queue<problem*, vector<problem*>, MoveCost> &statequeue, std::vector<problem*> &solutions, std::set<vector<int>> &repeats, int &maxsize, int &expanded){
    problem* root = initial_state;
    problem* goalNode = NULL;
    std::set<vector<int>> foundSet;

    std::cout << "Expanding state";
    root->print();

    statequeue.push(root);

    if(root->solutionfound()){
        return root;
    }

    while(!statequeue.empty()){
        if(statequeue.size() > maxsize){
            maxsize = statequeue.size();
        }
        initial_state = statequeue.top();
        if(initial_state->gDistance != 0){
            //std::cout << "The best state to expand with g(n) = " << initial_state->gDistance << " and h(n) = " << initial_state->heuristic << "is ...\n";
            //initial_state->print(); 
        }
        statequeue.pop();

        if(goalNode != NULL && (goalNode->solutionfound() && (goalNode->totalCost <= statequeue.top()->totalCost))){
            return goalNode;
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
                    if(expansions.at(i)->solutionfound()){
                        goalNode = expansions.at(i);
                    } 

                }
            }
        }
    }

    return NULL;
    //NEXT EXPANSION
    /*cout << "The best state to expand with g(n) = " << statequeue.at(0)->gDistance << " and h(n) = " << statequeue.at(0)->heuristic << " is..." << endl;
    statequeue.at(0)->print();
    cout << "   Expanding this node..." << endl << endl;
    */
}