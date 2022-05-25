<h1 align="center"> Project #2 - Feature Selection with Nearest Neighbor (Machine Learning)</h1>
<p align="center">CS170 - Spring 2022</p>
<p align="center">Author: Sumachai Suksanguan (ssuks001@ucr.edu), SSID #: 862012822

# Solution

![Search Stats](images/custom_stats.png)

## In completing this project, I consulted following resources:
<ul>
<li><a href="https://developers.google.com/machine-learning/data-prep/transform/normalization">Normalization in Machine Learning</a>
<li><a href="https://scikit-learn.org/stable/modules/generated/sklearn.preprocessing.StandardScaler.html">Standard Deviation in Datasets</a>
<li><a href="https://www.analyticsvidhya.com/blog/2020/10/feature-selection-techniques-in-machine-learning/">Feature Selection in Machine Learning Overview</a>
</ul>

# Introduction

The basis of this assignment was to design a system that was able to take a `txt` file, parse the data from it, and from the dataset contained within the file, create an algorithm that is able to determine which subset of features is best suited as a "learning model" for our machine.  

Creating a system of such scale may present several issues that require the student wrap their head around, and it may be difficult if you don't split it up modularly.  As a result, the soft deadlines allowed me to view the code draconically, and design a solution, that was tweaked minimally at the end when combined during phase three.
<ol>
<li> A Dummy Driver, that uses Random Evaluation and Greedy Selection
<li> Implementing Accuracy Evaluation
<li> Combining the two, into one file
</ol>

My design process, as well as how the functions were structured and created will be explained in detail in the later sections

To run the code, please run `make` in your terminal.  You will then see that two executable files are created, `data.exe` and `turnin.exe`.  `data.exe` may be used as one-time data tester to verify specific feature subsets and what they evaluate to.  `turnin.exe` is meant to be the fully functional executable.

# Challenges

The main challenge with this program was more conceptual on how to visualize the data.  For example, plotting one feature on a graph is simply a one-dimensional graph, two features is two-dimensional, and three-features is three-dimensional.  It starts to get really confusing to mentally picture it, once we start comparing and plotting multiple features!

Thankfully, most graphs can be solved via math, which our computers absolutely excel at.  Once I was able to generalize my code, I was able to create something that is completely functional, no matter what you throw at it.

# Code Design

As I mentioned above, the program was split into three phases, and during the first two phases, I created two individual classes to ensure that I knew how to correctly implement each required feature of the program.

## Phase 1 - Implementing the Search Algorithms

In this part of the project, we needed to implement two search methods: Forward Selection and Backwards Elimination.  Our algoritm would be greedy in nature, and select (at the moment), whichever child has the highest accuracy.  

The immediate issue at the moment is, how do we test that the algorithm works, if we don't have a way of testing the data and determining itss true accuracy? Well, we just use random numbers for now.

### Setup

In order to get this project flowing, we needed to first setup the program to accept our user input, and set up the program with all the information it needs to run properly.  During this time, we setup an arbitrary board with a number of features. We then prompt the user to indicate whether they want to use Forward Selection or Backwards Elimination

### `class problem`

Our program will mainly run off `problem` objects, and interacting with those objects.  At this moment though, the only thing that our object needs to correctly run, are these member variables:

```c++
class problem{
    private:
        std::vector<int> features;              // Features that are currently being tested or used
        std::vector<int> remaining_features;    // Features we have yet to test
        problem* parent;                        // Pointer to previous iteration
        double accuracy;                        // Randomly generated accuracy
```
Then, it has several member functions for easy interfacing.  While the majority of these are helper functions, and specific print functions, the main drivers of the code are the `generateForwardChild()` and `generateBackwardsChild()` functions:

```c++
class problem{
    public:
        problem();
        problem(int start, int choose);
        ~problem();

        //Generate Feature Children
        problem* generateForwardChild(int index);
        problem* generateBackwardsChild(int index);

        //Print Functions
        void print();
        void printBest();
        void printSolution();

        //Helper + Getter Functions
        void fillFeatureBank(int index, int select);
        double getAccuracy();
        std::vector<int> getVector();
        problem* getParent();
        int remainingSize();
        int frontierSize();
};
```






