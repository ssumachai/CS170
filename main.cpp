#include "problem.h"

int main(){
    std::vector<int> problemB = {};
    std::vector<int> solution = {};
    
    setup(solution, problemB);
    problem* tileBoard = new problem(problemB, number_rows, number_columns);

    std::cout << "Misplaced Tiles: " << tileBoard->misplacedCost() << std::endl;   
    std::cout << "Manhattan Distance: " << tileBoard->euclideanCost() << std::endl;
}