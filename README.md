<h1 align="center">Project #1 - The Eight Puzzle</h3>
<p align="center">CS170 - Spring 2022</p>
<p align="center">Author: Sumachai Suksanguan (ssuks001@ucr.edu), SSID #: 862012882

# Premise

A sliding puzzle, sliding block puzzle, or sliding tile puzzle is a combination puzzle that challenges the players to slide pieces along certain routes to establish a certain end-configuration.  Traditionally, tiles will be numbered, and the goal is have all numbered tiles in ascending order.  Popular variations can include displaying an image.

Typically, while this is a game that can be played by all ages, is there a way we can capture the problem, and solve it via AI?  Yes, as a matter of fact most problems can now be solved by an AI, it's just a matter of how we scope and design the problem!

# Design

Before we can even begin designing our code, we need to fundamentally break down how we can even set this problem up as something a computer can solve. We need a data structure that can easily hold values, that allows for easy swapping and moving of internal elements during runtime, and easy pushback and appending during setup, come, the vector.

Example, the following "board" can be represented by the corresponding vector:

```
1 2 3
4 5 6
7 8 0
```
> Note: 0 represents the blank tile
```c++
std::vector<int> board = {1, 2, 3, 4, 5, 6, 7, 8, 0};
```

The menu interface is not something that needs to explained in detail, besides that it functions as a way to accept correct input, and does not proceed further into the problem unless correct input is received.

The program will start by asking users if they would like a hard-coded default board, or a custom board.  It will then ask them to select an algorithm.  Once both things are met successfully, the program will run the `setup()` function, which will then generate the board they asked for, whether it be a hard-coded simple one, or a custom board, followed by the solution board.

## `class problem`

Once the problem and solution board have been created and filled, it's time to utilize the `class problem` to really drive our code.  The class contains five private member variables:
```c++
class problem{
    private:
        std::vector<int> currBoard;
        std::vector<int> goalBoard;
        int num_rows;
        int num_columns;
        int boardSize;
}
```
The two vectors are self-explanatory, as we always need a way to refernce the current state of our board, as well as compare it with the target state.
The three integers below it are utilized by move functions, as well as for location checking of indices.
It then has several public member variables, as well as functions, that are used to move the board:
```c++
class problem{
        public:
        problem();
        problem(std::vector<int> v, int rows, int columns);
        ~problem();
        problem* parent;
        double totalCost;           // f(n) = g(n) + h(n)
        double heuristic;           // h(n) = estimated distance from n to the goal
        double gDistance;           // g(n) = cost to get from node n from initial state
        int findBlankIndex();
        problem* moveUp();
        problem* moveDown();
        problem* moveLeft();
        problem* moveRight();
        int misplacedCost();
        int euclideanCost();
        void print();
}
```
The constructors and destructors do what they are designed to do, but the main focus of the code are on its move functions, and heuristic calculators.
## Move Functions
When searching for a solution, we found out it would be best to generalize movement as much as possible.  While it is very easy to implement a hardcoded solution for each specific tile, you quickly begin to realize a pattern that can be used to move the tiles, or rather elements of a vector.
Before we start, please note that the move functions are moving the blank space specifically.  If the function is called `moveup()`, it is moving the blank space up on the board.  If it is called `moveDown()`, it is moving the blank space down on the board.
### Finding the Blank Space
Because our move functions are moving the blank space specifically, we created a helper function that searches for the blank space within the initial board (`currBoard`), and then returns the index value.
### Determining which moves are Illegal (or can't be made)
When sliding tiles, there are some moves you just can't make.  If the blank space is on the topmost row, you can't "move the blank space up", because there is no where to move it
For the upcoming section, please use this sample tile puzzle as a reference:
```
1 2 3
4 0 5
6 7 8
```
|Direction | "Illegal" Indices | Index as a function                      | Index to Swap With | Index as formula    |
| -------- | ----------------- | ---------------------------------------- | ------------------ | ------------------- |
| Up       | 0, 1, 2           | index < num_columns                      | 1                  | index - num_columns |
| Down     | 6, 7, 8           | index >= (num_columns)*(num_columns - 1) | 7                  | index + num_columns |
| Left     | 0, 3, 6           | index % num_columns == 0                 | 3                  | index - 1           |
| Right    | 2, 5, 8           | index + 1 % num_columns == 0             | 5                  | index + 1           |
### Determining Heuristics
#### Misplaced Tile
A really simple algorithm, just iterate through both vectors and compare the first n-1 elements.  If they do not match, increment the counter by one, then return that counter to get number of Misplaced Tiles.
#### Manhattan Distance (Euclidean)
The Manhattan Distance formula is given by: `sqrt((a1 - b1)^2 + (a2-b2)^2)`
Where:
<ul>
<li>a<sub>1</sub> represents current X Position
<li>b<sub>1</sub> represents true X Position
<li>a<sub>2</sub> represents current Y Position
<li>b<sub>2</sub> represents true Y Position
</ul>
Iterate through the board, and if the current tile on the currBoard does not match the respective tile, then calculate all the appropriate values via our formulas, and then update the count and return it.

# Search Functions

The goal of this assignment was to implement the following search algoritms when it came to solving our board:
<ul>
<li> Uniform-Cost Search
<li> A* Search with Misplaced Tile Heuristic
<li> A* Search with Manhattan Distance Heuristic
</ul>

All these searches function the exact same way, by calculating the total cost of the move as such, `f(n) = g(n) + h(n)`.  Where `g(n)` represents distance from the root node, and `h(n)` is the heuristic value.

| Algorithm | Heuristic Value |
| --------- | --------------- |
| Uniform   | 0
| Misplaced | # of Misplaced Tiles
| Manhattan | Sum of Euclidean Distances of All Misplaced Tiles

As a result, all search functions follow the same template, except for one line of code:

```c++
problem* SEARCHTEMPLATE(problem* initial_state, std::priority_queue<problem*, std::vector<problem*>, MoveCost> &statequeue, std::vector<problem*> &solutions, std::set<std::vector<int>> &repeats, int &maxsize, int &expanded){
    problem* root = initial_state;
    std::set<std::vector<int>> foundSet;

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
                    expansions.at(i)->heuristic = 0 / expansions.at(i)->misplacedCost() / expansions.at(i)->euclideanCost();
                    expansions.at(i)->totalCost = expansions.at(i)->heuristic + expansions.at(i)->gDistance;
                    statequeue.push(expansions.at(i));
                    foundSet.insert(expansions.at(i)->getCurrBoard());
                }
            }
        }
    }

    return NULL;
}
```

In my code, there are three search functions, that will account for which value of the heuristic is used.  Besides that, the code follows the structure that we used in class.

<ol>
<li>Initialize the frontier using the initial state
<li>If the queue is not empty, continue running
<li>Choose leaf node and remove from frontier
<li>Check to see if that node is the goal, if not, add it to the explored set, then expand the leaf.
</ol>

# Optimizations and Personal Choices

I kept the strucutre of the code very similar to the lecture, but I did utilize an explored set to keep track of repeated nodes, as well as priority queue to keep track of the frontier.  The priority queue was built using a `CompareCost` structure, that allowed the queue to properly enqueuue board objects by checking their `totalCost`.

```c++
struct MoveCost{
    bool operator()(problem* const b1, problem* const b2){
        if(b1->totalCost == b2->totalCost){
            if(b1->gDistance < b2->gDistance){
                return false;
            }
        }
        else{
            return b1->totalCost > b2->totalCost;
        }
    }
};
```
# Heuristic Comparisons

## Maximum Queue Size

![Maximum Queue Size Graph](/images/queuesize.png)


|              | Uniform Cost Search | Misplaced Tile | Manhattan Distance |      
| ------------ | ------------------- | -------------- | ------------------ |
| Trivial (1)  | 1                   | 1              | 1
| Very Easy (2)| 3                   | 3              | 3 
| Easy (3)     | 4                   | 3              | 4
| Doable (4)   | 16                  | 5              | 7
| Oh Boy (5)   | Unreachable         | 4867           | 1745
|Impossible (6)| Unreachable         | Unreachable    | Unreachable

## Nodes Expanded Per Puzzle

![Nodes Expanded Per Puzzle](/images/node.png)

|              | Uniform Cost Search | Misplaced Tile | Manhattan Distance |      
| ------------ | ------------------- | -------------- | ------------------ |
| Trivial (1)  | 0                   | 0              | 0
| Very Easy (2)| 2                   | 2              | 2
| Easy (3)     | 5                   | 3              | 4
| Doable (4)   | 17                  | 4              | 7
| Oh Boy (5)   | 96812               | 8772           | 3163
|Impossible (6)| Unreachable         | Unreachable    | Unreachable
