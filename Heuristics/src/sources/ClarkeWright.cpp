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

		float alfa=0.4;
		float beta=0.4;

		for(alfa=0.4;alfa<=2.1;alfa=alfa+0.2)
		{
			for(beta=0.4;beta<=2.1;beta=beta+0.2)
			{
				savingsAlreadyDone.clear();
				savingData.clear();
				routes.clear();
				orderedSavings.clear();

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


				//merge routes
				for(int i=0; i<orderedSavingsSize; i++)
				{
					//get top saving
					saving=popElement(&orderedSavings);
					savingObj=savingData[saving];

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

				printf("\n\nAlfa : %f, Beta: %f\n\n", alfa, beta);
				dump(routes, problemData, true);
				printf("\n\n");
			}

		}

		printf("END");

	}



	int ClarkeWright::popElement(vector<int>* orderedSavings)
	{
		int element = orderedSavings->front();

		pop_heap(orderedSavings->begin(), orderedSavings->end());
		orderedSavings->pop_back();

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


