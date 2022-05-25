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

### Code Logic

Both `generateForwardChild()` and `generateBackwardsChild()` follow the same code structure, the only difference is that they check each one uses a different vector to determine what should be checked next.  Forward Selection adds stuff to be checked to the `features` vector, while Backwards Elimation constantly pops from `features` and checks that instead.

```c++
problem* problem::generateForwardChild(int index){
    problem* temp = new problem();
    temp->problem_set = this->problem_set;
    temp->tester = this->tester;
    temp->features = getVector();
    temp->features.push_back(remaining_features.at(index));
    temp->accuracy = tester->accuracy(temp->features);
    
    std::vector<int> temp_rem = this->remaining_features;

    temp_rem.erase(temp_rem.begin() + index);

    temp->remaining_features = temp_rem;
    temp->parent = this;

    if(parent != NULL){
        if(parent->accuracy > temp->accuracy){
            accuracy_decreased = true;
        }
    }

    return temp;
}

problem* problem::generateBackwardsChild(int index){
    problem* temp = new problem();
    temp->problem_set = this->problem_set;
    temp->tester = this->tester;
    std::vector<int> temp_rem = getVector();
    temp_rem.erase(temp_rem.begin() + index);
    temp->features = temp_rem;
    temp->accuracy = tester->accuracy(temp->features);
    temp->remaining_features = this->remaining_features;
    temp->parent = this;

    if(parent != NULL){
        if(parent->accuracy > temp->accuracy){
            accuracy_decreased = true;
        }
    }

    return temp;
}
```

> Note: Both these functions are nearly identical, with the exception of how they manipulate the `features` vector.  Forward Selection uses the `features` vector as a queue that they add to, while Backwards Elimination pops from it.

How the algorithms run and function will be explained in much further detail below!

## Phase 2 - Implementing Evaluation Function and Nearest Neighbor

For the next phase of the project, I wanted to create a program that would allow me to parse through the provided data sets, build the training model, and then test how certain feature subsets affect the accuracy.  The main purpose of this program is to ensure that the testing method works, and for that, I developed three additional classes:

<ul>
<li> dataset
<li> classifier
<li> validator
</ul>

But how exactly does our data "live"?  The way the program is setup, is that it will prompt the user to select a dataset, and then the dataset will be parsed into a `classifier` object!  Each column of data is parsed, and turned into an object of type `dataset`, which is then pushed into a vector that contains those datasets, which is a member variable of `class classifier`!

### `class classifier`

As you can see, the class `classifier` can be defined below:

```c++
class classifier{
    private:
        std::vector<dataset*> datasets;
    public:
        // Constructors & Destructors
        classifier();
        ~classifier();

        // Train and Test Functions
        void parse();                                           // Also known as train()
        int test(int instance_index, std::vector<int> subsets); // Test function
        
        // Normalize Data required for Calculating Distance
        void normalizeData();

        // Distance Helper Function
        double getDistance(dataset* a, dataset* b, std::vector<int> features);

        // Getter Helper Functions
        double getDefaultRate();
        int getDataSize();
        int getFeatureSize();
        int getClassLabel(int i);

        // Void Helper Functions 
        void print();
        void subsetInput(std::vector<int> &f);
};
```

There are multiple getter helper functions that allow us to access the data in the private variables, and then a normalization utility function that normalizes all the data in their respective columns!

But why does this all matter?  The way <b>Leave-One-Out Validation</b> works, is that we create the training model based on the entire data set, with the exception of one entry, then "test" that entry in our code.  If that entry tests correctly, it improves the accuracy of that feature subset.  If it doesn't, then it decreases the accuracy.  We iterate through all datasets, excluding one specific entry each time until we finish the data set!

But how do we actually test it? and How does it know if it's successful?  That's where `getDistance()`, `test()`, and a member function from class `validator`, `accuracy()` comes into play.

### Evaluation

After we construct our dataset, which lives in object `classifier`, we then create a `validator` object that contains that classifier, and then use that to test our data!

`validator::accuracy()` iterates through the entire classifier, and performs Leave-One-Out Validation with whatever feature subset is provided to it.  During this phase, the user provides the feature subset via input.

```c++
double validator::accuracy(std::vector<int> featureSubset){
    int correct = 0;
    int result = 0;
    double percentage = 0;

    for(int i = 0; i < myClass->getDataSize(); i++){
        result = myClass->test(i, featureSubset);
        if(result == myClass->getClassLabel(i)){
            correct++;
        }
    }

    percentage = (double)correct / (double)myClass->getDataSize();

    return percentage;
}
```

Again, if the predicted subset is correct, it increases our accuracy, and if not, it decreases it.  It then returns the percentage, which is then used in the greedy search we implemented earlier!

### How do we determine the predicted label though?

Leave-One-Out is used to validate and test the data extensively, but at the smallest level, we need a way to evaluate the distance between one instance and another, which is where the `getDistance()` utility function comes into play.

`getDistance()` takes in two dataset instances as input, along with the features subset that it is evaluating, and then calculates the Euclidean distance between the two.

```c++
double classifier::getDistance(dataset* a, dataset* b, std::vector<int> features){
    std::vector<double> under = {};
    // Compute Stuff Underneath the Square Root

    for(int i = 0; i < features.size(); i++){
        double temp = b->getFeatureValue(features[i]) - a->getFeatureValue(features[i]);
        temp = pow(temp, 2);
        under.push_back(temp);
    }

    // Compute Sum of stuff under the square root

    double under_sum = 0;

    for(int i = 0; i < under.size(); i++){
        under_sum += under[i];
    }

    return std::sqrt(under_sum);
}
```

Remember, that the structure for calculating Euclidean Distance is as follows: $\sqrt{k}$, where k is represented as $\sum_{i=1}^{i=n} (x_i - y_i)^2$.

In the above code, the first `for` loop calculates every that goes under the square root, by iterating through the list of features it needs to check and compare, and then summing them all together.

Example, if given feature subset {1, 2, 4}, calculate the sum of the difference in distance from Instance A and Instance B at features 1, 2, and 4, and then sum them all together.

Then simply take the square root of the summation to get the Distance.

### Calculating Nearest Neighbor

Now that we have utility function that calculates the distance of two given points, we need to actually determine if that is the nearest neighbor.  Nearest neighbor is calculated in the `test()` function, by comparing the distance of the current test with the local minimum.

```c++
int classifier::test(int instance_index, std::vector<int>subsets){
    dataset* testInstance = datasets[instance_index];
    dataset* currentNearest = new dataset();

    double closest = std::numeric_limits<double>::max();
    for(int i = 0; i < datasets.size(); i++){
        if(i == instance_index){
            continue;
        }
        double eucl = getDistance(datasets[instance_index], datasets[i], subsets);
        if(eucl < closest){
            closest = eucl;
            currentNearest = datasets[i];
        }
    }

    return currentNearest->getInstance();
}
```

Start by initializing `double closest` to the highest possible number.  If you test an instance, and get a lower distance, update that variable, as well as designating that instance as the nearest neighbor.  At the end of `test()` return the class label of the nearest instance as the predicted label.

## Phase 3 - Connecting Everything

In phase 1, we implemented the greedy search which would determine which feature subset yielded the greatest accuracy.  And in phase 2, we implemented the evaluation method that allowed us to test how each feature subset fares.  But the thing about phase 2, is that the code was driven by user input...and we need this to be automated...so now, we need to drive the search logic, and "teach" the system how to use that!

And it's actually quite simple.  We take our very simple `problem` object, that only initially had a few member variables, and we give it access to what drives the data testing...we give it access to `classifier` and `validator` and we make those a part of it.  So now `class problem` looks a little more like this:

```c++
class problem{
    private:
        classifier* problem_set;
        validator* tester;
        std::vector<int> features;
        std::vector<int> remaining_features;
        problem* parent;
        double accuracy;
        bool accuracy_decreased;
```

So phase 1, we taught the program how to make decisions.  And phase 2, we implemented how the decisions measure up.  Now, we let the code drive itself, and evaluate and make it's own decisions!

The code we wrote in phase 1 already determines which subsets to use via manipulation and control of the `features` vector.  The code we wrote in phase 2 takes in a `features subset` vector as input, and uses that to perform a accuracy test on that specific subset in that particular dataset.  All we have to do, is automate it.

Which is simple!  Everytime `generateForwardChild()` or `generatedBackwardsChild()` runs, it manipulates the `features` vector in the appropriate manner, all we need to do is pass `features` into `validator::accuracy()` to test that specific feature subset.  What then happens is it the search algorithm will go through all possible children, obtain the best one, and then continue to narrow it down!  Completely automated!

# Dataset Details

For this assignment, I was assigned <b>Dataset 155</b>.  Both datasets are linked below:
<ul>
<li> <a href="datasets/personal_small_dataset.txt">Small Personal Set</a> - (100 Instances, 10 Features)
<li> <a href="datasets/personal_large_dataset.txt">Large Personal Set</a> - (1000 Instances, 40 Features)
</ul>

# Algorithms

## How Do we Search?

Once the user inputs which algorithm to use, Forward Selection recursively looks for the answer with `generateForwardChild()` and Backward Elimination recursively looks for the answer with `generateBackwardsChild()`.

Each function does exactly what it says it does:

`generateForwardChild()` looks to see which features have yet to be "explored" and then obtains the accuracy of that proposed child.  For example, in an empty problem set, where we have 4 features total, it will check to see the accuracy of using features 1, 2, 3 and 4.

```
Using features() {1} accuracy is 0.4
Using features() {2} accuracy is 1
Using features() {3} accuracy is 0.7
Using features() {4} accuracy is 0.531
```

All these tests are "children" that are added into a priority queue. It then greedily selects the <b>highest</b> accuracy from the pool by selecting the top of the queue, and then further expanding that.  In this example, it will select the second feature, because it has the highest accuracy at 1.

Then, once feature 2 is locked in, it will then see if there are any further routes it may possibly take!  Feature two has been selected, which means that it can potentially combined with feature 1, feature 3, or feature 4.

```
Using features() {1, 2} accuracy is 0.4
Using features() {3, 2} accuracy is 0.8
Using features() {4, 2} accuracy is 0.312
```

Then, it would select features 3 and 2, because it's the current highest child!  Features 3 and 2 have been explored, and now we have 1 and 2 left.

```
Using features() {1, 3, 2} accuracy is 0.123
Using features() {4, 3, 2} accuracy is 0.42
```

We would then select the second option, as it is the child with the highest accuracy!  We then only have the last feature, 1, left to expand.

```
Using features() {1, 4, 3, 2} accuracy is 0.512
```

At this point, that becomes our solution state, as it's the final state where all features have been explored.  From there, we find the state that has the highest accuracy!  We do this, by constantly checking the states parents nodes, and the node with the highest accuracy is the best subset!

In the above example, there are the states we explored, and their accuracys:

```
Using features() {} accuracy is 0.31
Using features() {3} accuracy is 0.7
Using features() {3, 2} accuracy is 0.8
Using features() {4, 3, 2} accuracy is 0.42
Using features() {1, 4, 3, 2} accuracy is 0.512
```

Based on this, using features {3, 2} yield the highest accuracy at 0.8!  At this point, we have yet to implement a true evaluation function, but this is the basis of how the algorithm should work!  We just need to ensure that the greedy selection is selecting the best possible option at expansion, and then expanding.

## What about Backwards Elimation?

Backwards Elimination works exactly the same as Forward Selection, but rather than exploring one feature at a time, we have all features at the start, and remove one feature at a time, check the accuracy, and then greedily select which one yields the highest accuracy after removal!  Using the same method as above, and using `generateBackwardsChild()` to recursively find the solution board.

So assuming we use the same problem state as earlier, the trace would look something like this:

<b>Assume that using all features has an accuracy of 0.24</b>

```
Using features() {2, 3, 4} accuracy is 0.12
Using features() {1, 3, 4} accuracy is 0.65
Using features() {1, 2, 4} accuracy is 0.76
Using features() {1, 2, 3} accuracy is 0.61
```

Based on this info, we see that if we remove feature 3, it actually yields the highest accuracy at 0.76! So we remove feature 3, and then expand from there!

```
Using features() {2, 4} accuracy is 0.52
Using features() {1, 4} accuracy is 0.13
Using features() {1, 2} accuracy is 0.62
```

Feature 3 has already been removed, and now we see that if we remove feature 4, it yields a much higher accuracy, so we remove feature 4 and move forward

```
Using features() {1} accuracy is 0.5
Using features() {2} accuracy is 0.9
```

Features 3 and 4 have been removed, and we are now testing removing either feature 2 or 1.  Removing feature 1 is the highest one, so we remove feature 2 and then 1.

```
Using features() {} accuracy is 0.13
```

We then do as we did above, and look for the maximum from the entire tree.

```
Using features() {1, 2, 3, 4} accuracy is 0.24
Using features() {1, 2, 4} accuracy is 0.76
Using features() {1, 2} accuracy is 0.62
Using features() {2} accuracy is 0.9
Using features() {} accuracy is 0.13
```

Based on this, we should use only feature 2 as it yields the highest accuracy of 0.9!

# Analysis

## Experiment 1 - Comparing Forward Selection vs Backwards Elimination

## Experiment 2 - Not Normalizing the Data

## Experiment 3 - Effect of Number Neighbors (k)

# Conclusion


# Dataset Traces

All Traces to Data-Sets are provided in the folders, however here is the trace for the small personal set:

```
Insert Code Here
```


















