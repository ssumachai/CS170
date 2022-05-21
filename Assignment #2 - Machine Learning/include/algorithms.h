#ifndef __ALGORITHMS_H__
#define __ALGORITHMS_H__

#include "setup.h"

class problem;
#include "problem.h"



double getRandomEval();
problem* ForwardSelection(problem* startBoard);
problem* BackwardElimination(problem* startBoard);

#endif
