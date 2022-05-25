#ifndef __SETUP_H__
#define __SETUP_H__

#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>
#include <queue>
#include <algorithm>
#include <string>
#include <numeric>
#include <stdlib.h>
#include <math.h>
#include <limits>
#include <time.h>
#include "classifier.h"


using namespace std::chrono;

class classifier;

bool checkFeatureInput(int feature_count);
bool checkAlgorithmInput(int algo_input);
void setup(classifier* c, int &algo_select);

#endif