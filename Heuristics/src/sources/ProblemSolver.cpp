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
		map<int, int> demandSection = problemData.getDemandSection();
		int depot = problemData.getDepotSection() -1;
		int capacity=problemData.getCapacity();
		map<int, map<int, bool> > savingsAlreadyDone;
		map<int, saving_obj*> savingData;
		map<int, route_data*> routes;
		vector<int> orderedSavings;
		int orderedSavingsSize;
		saving_obj* savingObj;
		route_data* routeData;
		vector<int> route;
		int routeIndexForMerge1;
		int routeIndexForMerge2;
		int saving;
		route_data* routeDataForMerge1;
		route_data* routeDataForMerge2;
		bool isSavingAlreadyDone;

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
				routeData->demandSum=demandSection[i];

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
		orderedSavingsSize=orderedSavings.size();

		for(int i=0; i<orderedSavingsSize; i++)
		{
			//get top saving
			saving=popElement(&orderedSavings);
			savingObj=savingData[saving];

			isSavingAlreadyDone= (savingsAlreadyDone[savingObj->node1][savingObj->node2] || savingsAlreadyDone[savingObj->node1][savingObj->node2]);

			if(!(isSavingAlreadyDone))
			{
				//check if exists routes (i,0) and (0,j)
				routeIndexForMerge1=checkForRoute(routes, savingObj->node1, depot);
				routeIndexForMerge2=checkForRoute(routes, depot, savingObj->node2);

				if(routeIndexForMerge1 != -1 && routeIndexForMerge2 != -1)
				{
					routeDataForMerge1=routes[routeIndexForMerge1];
					routeDataForMerge2=routes[routeIndexForMerge2];

					//check sum capacity

					if(routeDataForMerge1->demandSum + routeDataForMerge2->demandSum <= capacity)
					{
						route.clear();

						printf("\nSTAMPO PRIMA ROUTE\n");
						for(size_t i=0; i< routeDataForMerge1->route.size(); i++)
						{
							printf("%d -- ", routeDataForMerge1->route[i]);
						}
						printf("\nSTAMPO SECONDA ROUTE\n");
						for(size_t i=0; i< routeDataForMerge2->route.size(); i++)
						{
							printf("%d -- ", routeDataForMerge2->route[i]);
						}

						//i,0 e' sempre alla fine della prima route mentre 0,j e' sempre all'inizio della seconda
						route.assign(routeDataForMerge1->route.begin(), routeDataForMerge1->route.end()-2);
						route.push_back(savingObj->node1);
						route.push_back(savingObj->node2);
						route.insert(route.end(), routeDataForMerge2->route.begin()+2, routeDataForMerge2->route.end());

						savingsAlreadyDone[savingObj->node1][savingObj->node2]=true;

						printf("\nSTAMPO ROUTE FUSA\n");
						for(size_t i=0; i< route.size(); i++)
						{
							printf("%d -- ", route[i]);
						}

						routeDataForMerge1->route = route;
						routeDataForMerge1->demandSum = routeDataForMerge1->demandSum + routeDataForMerge2->demandSum;

						routeDataForMerge2=NULL;

						routes[routeIndexForMerge1]=routeDataForMerge1;
						routes.erase(routeIndexForMerge2);
					}

				}
			}
		}


		dump(routes, problemData);

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


	void ProblemSolver::dump(map<int, route_data*> routes, ProblemData problemData)
	{
		route_data* routeData;
		vector<int> route;
		vector<vector<int> > edgeWeightSection = problemData.getEdgeWeightSection();

		int fo=0;

		printf("\nInizio a dumpare routes\n");
		for(map<int, route_data*>::iterator it = routes.begin(); it != routes.end(); ++it)
		{
			routeData = routes[it->first];
			route=routeData->route;

			printf("\nRoute n %d\n", it->first);

			for(size_t i=0; i< route.size() -1; i++)
			{
				printf("%d -- ", route[i]);
				fo+=edgeWeightSection[route[i]][route[i+1]];
			}
			printf("%d -- ", route[route.size()-1]);

			printf("\nFINE ROUTE\n ");
		}

		printf("\nFUNZIONE OBIETTIVO : %d\n", fo);

	}


