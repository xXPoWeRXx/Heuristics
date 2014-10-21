/*
 * ProblemSolver.h
 *
 *  Created on: Oct 14, 2014
 *      Author: alex
 */

#ifndef PROBLEMSOLVER_H_
#define PROBLEMSOLVER_H_

#include "ProblemData.h"
#include <algorithm>

using std::make_heap;
using std::pop_heap;

class ProblemSolver
{
	public:
    struct saving_obj
    {
       int node1;
       int node2;
       int saving;
    };
	ProblemSolver(){};
	static void solve(ProblemData problemData);

	private:
	static void computeSavings(ProblemData problemData);
	static int popElement(vector<int>* orderedSavings);

};



#endif /* PROBLEMSOLVER_H_ */
