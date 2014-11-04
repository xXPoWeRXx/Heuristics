/*
 * ProblemSolver.cpp
 *
 *  Created on: Oct 14, 2014
 *      Author: alex
 */

#include "../headers/ClarkeWright.h"
#include <stdio.h>



	void ClarkeWright::solve(ProblemData problemData)
	{

		vector<vector<int> > edgeWeightSection=problemData.getEdgeWeightSection();
		map<int, int> demandSection = problemData.getDemandSection();
		int depot = problemData.getDepotSection() -1;
		int capacity=problemData.getCapacity();
		map<int, map<int, bool> > savingsAlreadyDone;
		vector<saving_obj*> savingData;
		map<int, route_data*> routes;
		int orderedSavingsSize;
		saving_obj* savingObj;
		route_data* routeData;
		vector<int> route;
		int routeIndexForMerge1;
		int routeIndexForMerge2;
		float saving;
		route_data* routeDataForMerge1;
		route_data* routeDataForMerge2;
		bool isSavingAlreadyDone;

		float alpha=0.4;
		float beta=0.4;

		for(alpha=1.0;alpha<=1.1;alpha=alpha+0.2)
		{
			for(beta=1.0;beta<=1.1;beta=beta+0.2)
			{
				savingsAlreadyDone.clear();
				savingData.clear();
				routes.clear();

				//compute savings
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
								saving = (alpha * (edgeWeightSection[i][depot] + edgeWeightSection[depot][j])) - ( beta * (edgeWeightSection[i][j]));
								if(saving>0)
								{
									savingObj = new saving_obj;

									savingObj->node1=i;
									savingObj->node2=j;
									savingObj->saving=saving;

									//add savingData for ordering
									savingData.push_back(savingObj);
								}
							}
						}
					}
				}

				//order savings
				make_heap(savingData.begin(), savingData.end(), Comp());
				orderedSavingsSize=savingData.size();

				//merge routes
				for(int i=0; i<orderedSavingsSize; i++)
				{
					//get top saving
					savingObj=popElement(&savingData);

					isSavingAlreadyDone= (savingsAlreadyDone[savingObj->node1][savingObj->node2] || savingsAlreadyDone[savingObj->node2][savingObj->node1]);

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

								//i,0 is always at 1st route ending -- 0,j is always at 2nd route beginning
								route.assign(routeDataForMerge1->route.begin(), routeDataForMerge1->route.end()-2);
								route.push_back(savingObj->node1);
								route.push_back(savingObj->node2);
								route.insert(route.end(), routeDataForMerge2->route.begin()+2, routeDataForMerge2->route.end());

								savingsAlreadyDone[savingObj->node1][savingObj->node2]=true;

								routeDataForMerge1->route = route;
								routeDataForMerge1->demandSum = routeDataForMerge1->demandSum + routeDataForMerge2->demandSum;

								routeDataForMerge2=NULL;

								routes[routeIndexForMerge1]=routeDataForMerge1;
								routes.erase(routeIndexForMerge2);
							}
						}
					}
				}

				printf("\n\nAlpha : %f, Beta: %f\n\n", alpha, beta);
				dump(routes, problemData, false);
				printf("\n\n");
			}

		}

		printf("END");

	}



	ClarkeWright::saving_obj* ClarkeWright::popElement(vector<saving_obj*>* savingData)
	{
		saving_obj* element = savingData->front();

		pop_heap(savingData->begin(), savingData->end(), Comp());
		savingData->pop_back();

		return element;
	}



	int ClarkeWright::checkForRoute(map<int, route_data*> routes, int node1, int node2)
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


	void ClarkeWright::dump(map<int, route_data*> routes, ProblemData problemData, bool onlyFO)
	{
		route_data* routeData;
		vector<int> route;
		vector<vector<int> > edgeWeightSection = problemData.getEdgeWeightSection();

		int fo=0;

		if(!onlyFO)
		{
			printf("\nInizio a dumpare routes\n");
		}

		for(map<int, route_data*>::iterator it = routes.begin(); it != routes.end(); ++it)
		{
			routeData = routes[it->first];
			route=routeData->route;

			if(!onlyFO)
			{
				printf("\nRoute n %d\n", it->first);
			}

			for(size_t i=0; i< route.size() -1; i++)
			{
				if(!onlyFO)
				{
					printf("%d -- ", route[i]);
				}
				fo+=edgeWeightSection[route[i]][route[i+1]];
			}

			if(!onlyFO)
			{
				printf("%d -- ", route[route.size()-1]);
				printf("\nFINE ROUTE\n ");
			}
		}

		printf("\nFUNZIONE OBIETTIVO : %d\n", fo);

	}


