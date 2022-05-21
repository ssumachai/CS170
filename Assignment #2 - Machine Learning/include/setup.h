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


using namespace std::chrono;

bool checkFeatureInput(int feature_count);
bool checkAlgorithmInput(int algo_input);
void setup(int &feature_count, int &algo_select);

#endif