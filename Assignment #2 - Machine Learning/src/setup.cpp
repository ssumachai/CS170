#include "../include/setup.h"

void setup(classifier* c, int &algo_select, int &knn){

    int buffer;
    bool algo_selected = false;
    bool neighbor_selected = false;
    std::string temp_message;

    std::cout << "Welcome to Chai's Feature Selection Algorithm.\n";
    
    c->parse();

    std::cout << "Type the number of the algorithm you want to run.\n\n";
    std::cout << "[1] - Forward Selection\n[2] - Backward Elimination\n";
    std::cin >> buffer;

    while(!algo_selected){
        switch(buffer){
            case 1:
                std::cout << "\nUse Forward Selection Algorithm\n\n";
                algo_selected = true;
                break;
            case 2:
                std::cout << "\nUse Backward Elimination Algorithm\n\n";
                algo_selected = true;
                break;
            default:
                std::cout << "Invalid Input, please try again: ";
                std::cin >> buffer;
                break;
        }
    }

    algo_select = buffer;

    std::cout << "Type the number of the Nearest Neighbors you want to run. (Default is 1)\n\n";
    std::cout << "[1] - Default\n[3]\n[5]\n";
    std::cin >> buffer;

    while(!neighbor_selected){
        switch(buffer){
            case 1:
                std::cout << "\nUsing 1 Nearest Neighbor Evaluation\n\n";
                neighbor_selected = true;
                break;
            case 3:
                std::cout << "\nUsing 3 Nearest Neighbors Evaluation\n\n";
                neighbor_selected = true;
                break;
            case 5:
                std::cout << "\nUsing 5 Nearest Neighbors Evaluation\n\n";
                neighbor_selected = true;
                break;
            default:
                std::cout << "Invalid Input, please try again: ";
                std::cin >> buffer;
                break;
        }
    }

    knn = buffer;
}