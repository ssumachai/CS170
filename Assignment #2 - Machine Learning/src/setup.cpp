#include "../include/setup.h"

void setup(classifier* c, int &algo_select){

    int buffer;
    bool algo_selected = false;
    std::string temp_message;

    std::cout << "Welcome to Chai's Feature Selection Algorithm.\n";
    
    c->parse();

    std::cout << "Type the number of the algorithm you want to run.\n";
    std::cout << "[1] - Forward Selection\n[2] - Backward Elimination\n";
    std::cin >> buffer;

    while(!algo_selected){
        switch(buffer){
            case 1:
                std::cout << "Use Forward Selection Algorithm\n";
                algo_selected = true;
                break;
            case 2:
                std::cout << "Use Backward Elimination Algorithm\n";
                algo_selected = true;
                break;
            default:
                std::cout << "Invalid Input, please try again: ";
                std::cin >> buffer;
                break;
        }
    }

    algo_select = buffer;
}