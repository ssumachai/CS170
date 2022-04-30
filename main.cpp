#include <iostream>

void setup(){
    int boardInput = 0;
    bool board_select, algo_select = false;
    std::string temp_message;

    std::cout << "Welcome to Chai and Nikki's Board Tile solver!\n";
    std::cout << "1 -- Hardcoded Tile Board\n2 -- Custom Tile Board\n";

    std::cout << "Please enter your selection (1/2): ";
    std::cin >> boardInput;

    while(!board_select){
        switch(boardInput){
            case 1:
                temp_message = "Do Hardcoded Board Stuff\n";
                board_select = true;
                break;
            case 2:
                temp_message = "Do Custom Board Stuff\n";
                board_select = true;
                break;
            default:
                std::cout << "Invalid Input, please try again: ";
                std::cin >> boardInput;
                break;
        }  
    } 

    std::cout << "1 -- Uniform Cost Search\n2 -- A* w/ Misplaced Tile\n3 -- A* w/ Euclidean Distance\n";
    std::cout << "Please enter your selection (1/2/3): ";
    std::cin >> boardInput;

    while(!algo_select){
        switch(boardInput){
            case 1:
                temp_message += "Do Uniform Cost Search\n";
                algo_select = true;
                break;
            case 2:
                temp_message += "Do Misplaced Heuristic\n";
                algo_select = true;
                break;
            case 3:
                temp_message += "Do Euclidean Heuristic\n";
                algo_select = true;
                break;
            default:
                std::cout << "Invalid Input, please try again: ";
                std::cin >> boardInput;
                break;
        }
    }

    std::cout << temp_message;
    
}

int main(){
    setup();
}