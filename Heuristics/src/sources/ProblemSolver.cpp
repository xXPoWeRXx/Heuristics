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
		map<int, route_data*> routes;
		vector<int> orderedSavings;
		saving_obj* savingObj;
		route_data* routeData;
		vector<int> route;

		int saving;

		for(size_t i=0; i < edgeWeightSection.size();i++)
		{
			if(depot!=i)
			{
				routeData=new route_data;

				route.clear();
				route.push_back(depot);
				route.push_back(i);
				route.push_back(depot);

				routeData->route=route;
				routeData->demandSum=edgeWeightSection[depot][i] + edgeWeightSection[i][depot] + edgeWeightSection[depot][i];

				routes[i]=routeData;

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



	int ProblemSolver::checkForRoute(map<int, route_data*> routes, int node1, int node2)
	{
		route_data* routeData;
		vector<int> route;

		for(map<int, route_data*>::iterator it = routes.begin(); it != routes.end(); ++it)
		{
			routeData = routes[it->first];
			route=routeData->route;

			for(size_t i=0; i< route.size()-1; i++)
			{
				if(route[i]==node1)
				{
					if(route[i+1]==node2)
					{
						return it->first;
					}
				}
			}
		}

		return -1;
	}
