/*
 * ProblemSolver.cpp
 *
 *  Created on: Oct 14, 2014
 *      Author: alex
 */

#include "../headers/ProblemSolver.h"
#include <stdio.h>



	void ProblemSolver::solve(ProblemData problemData)
	{
		computeSavings(problemData);
	}


	void ProblemSolver::computeSavings(ProblemData problemData)
	{
		vector<vector<int> > edgeWeightSection=problemData.getEdgeWeightSection();
		int depot = problemData.getDepotSection() -1;
		map<int, saving_obj*> savingData;
		map<int, vector<int>*> routes;
		vector<int> orderedSavings;
		vector<int>* route;
		saving_obj* savingObj;

		int saving;

		for(size_t i=0; i < edgeWeightSection.size();i++)
		{
			if(depot!=i)
			{
				route = new vector<int>;

				route->push_back(depot);
				route->push_back(i);
				route->push_back(depot);

				routes[i]=route;

				for(size_t j=0; j < edgeWeightSection.size();j++)
				{
					if(i!=j && depot!=i && depot!=j)
					{
						saving = edgeWeightSection[i][depot] + edgeWeightSection[depot][j] - edgeWeightSection[i][j];
						if(saving>0)
						{
							savingObj = new saving_obj;

							savingObj->node1=i;
							savingObj->node2=j;
							savingObj->saving=saving;

							//add saving to savingData map
							savingData[saving]=savingObj;
							//add saving reference for ordering
							orderedSavings.push_back(saving);
						}
					}
				}
			}
		}

		//order savings
		make_heap(orderedSavings.begin(), orderedSavings.end());
		int max=popElement(&orderedSavings);

		printf("FINITO");
	}


	int ProblemSolver::popElement(vector<int>* orderedSavings)
	{
		int element = orderedSavings->front();

		pop_heap(orderedSavings->begin(), orderedSavings->end());
		orderedSavings->pop_back();

		return element;
	}
