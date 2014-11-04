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

class ClarkeWright
{
	public:
    struct saving_obj
    {
       int node1;
       int node2;
       int saving;
    };
    struct route_data
    {
       vector<int> route;
       int demandSum;
    };
    ClarkeWright(){};
	static void solve(ProblemData problemData);

	private:
	static int popElement(vector<int>* orderedSavings);
	static int checkForRoute(map<int, route_data*> routes, int node1, int node2);
	static void dump(map<int, route_data*> routes, ProblemData problemData, bool onlyFO);

};



#endif /* PROBLEMSOLVER_H_ */
