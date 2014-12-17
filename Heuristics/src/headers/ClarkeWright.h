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
#include <stdio.h>

using std::make_heap;
using std::pop_heap;

class ClarkeWright
{
	public:
    struct saving_obj
    {
       int node1;
       int node2;
       float saving;
    };
    struct route_data
    {
       vector<int> route;
       int demandSum;
    };
    struct Comp
    {
       bool operator()(const saving_obj* obj1, const saving_obj* obj2)
       {
           return obj1->saving < obj2->saving;
       }
    };
    ClarkeWright(){};
	static void solve(ProblemData problemData);

	private:
	static saving_obj* popElement(vector<saving_obj*>* savingData);
	static int checkForRoute(map<int, route_data*> routes, int node1, int node2);
	static void printRoutes(map<int, route_data*> routes, ProblemData problemData, FILE * resultFile);
	static int calculateFO(map<int, route_data*> routes, ProblemData problemData);

};



#endif /* PROBLEMSOLVER_H_ */
