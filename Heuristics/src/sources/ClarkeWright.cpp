/*
 * ProblemSolver.cpp
 *
 *  Created on: Oct 14, 2014
 *      Author: alex
 */

#include "../headers/ClarkeWright.h"
#include "../headers/FileManager.h"
#include <stdio.h>



	void ClarkeWright::solve(ProblemData problemData)
	{

		FILE * resultFile;
		vector<vector<int> > edgeWeightSection=problemData.getEdgeWeightSection();
		map<int, int> demandSection = problemData.getDemandSection();
		map<string, int> optimalSolutions=problemData.getOptimalSolution();
		int depot = problemData.getDepotSection() -1;
		string problemName=problemData.getName();
		int capacity=problemData.getCapacity();
		map<int, map<int, bool> > savingsAlreadyDone;
		vector<saving_obj*> savingData;
		map<int, route_data*> routesToPrint;
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
		int fo=-1;
		int optimalSolution=optimalSolutions[problemName];
		int weightSumCheck=optimalSolution;
		int weightSum;

		float gap=-1;
		int tempFo;

		int foA1B1=-1;
		map<int, route_data*> routesToPrintA1B1;

		float alpha;
		float beta;
		float alphaToPrint;
		float betaToPrint;

		clock_t begin;
		clock_t end;
		int cycles=0;
		double elapsedSecs=0;


		for(alpha=0.4;alpha<=2.1;alpha=alpha+0.2)
		{
			for(beta=0.4;beta<=2.1;beta=beta+0.2)
			{
				cycles++;
				begin = clock();

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
						routeData->demandSum=demandSection[i+1];
						routeData->weightSum=edgeWeightSection[depot][i] + edgeWeightSection[i][depot];

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

						if(routeIndexForMerge1 != -1 && routeIndexForMerge2 != -1 && routeIndexForMerge1 != routeIndexForMerge2)
						{
							routeDataForMerge1=routes[routeIndexForMerge1];
							routeDataForMerge2=routes[routeIndexForMerge2];

							//check capacity sum

							if(routeDataForMerge1->demandSum + routeDataForMerge2->demandSum <= capacity)
							{
								//check weight sum
								weightSum = routeDataForMerge1->weightSum + routeDataForMerge2->weightSum - edgeWeightSection[savingObj->node1][depot] - edgeWeightSection[depot][savingObj->node2] + edgeWeightSection[savingObj->node1][savingObj->node2];

								if(weightSum <= weightSumCheck )
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
									routeDataForMerge1->weightSum=weightSum;

									routeDataForMerge2=NULL;

									routes[routeIndexForMerge1]=routeDataForMerge1;
									routes.erase(routeIndexForMerge2);
								}
							}
						}
					}
				}

				end = clock();
				elapsedSecs+= double(end - begin) / CLOCKS_PER_SEC;

				tempFo=calculateFO(routes, problemData);

				if(fo<0 || fo>tempFo)
				{
					fo=tempFo;
					routesToPrint=routes;
					alphaToPrint=alpha;
					betaToPrint=beta;
				}

				if(alpha==1 && beta==1)
				{
					foA1B1=tempFo;
					routesToPrintA1B1=routes;
				}
			}

		}

		gap=100.00f * (fo - optimalSolution) / optimalSolution;

		resultFile = fopen(FileManager::getFilePath("result.txt").c_str(),"w");

		fprintf(resultFile, "RISULTATO:");
		fprintf(resultFile, "\n\nAlpha : 1, Beta: 1\n\n");
		printRoutes(routesToPrintA1B1, problemData, resultFile);
		fprintf(resultFile,"\nFunzione obiettivo : %d", foA1B1);

		fprintf(resultFile,"\n\n\n\nMIGLIORE SOLUZIONE TROVATA:\n");

		fprintf(resultFile,"\n\nAlpha : %f, Beta: %f\n\n", alphaToPrint, betaToPrint);
		printRoutes(routesToPrint, problemData, resultFile);

		fprintf(resultFile,"\nFunzione obiettivo : %d", fo);

		fprintf(resultFile,"\nSoluzione ottima (fornita): %d", optimalSolution);

		fprintf(resultFile,"\n\nGap tra la soluzione migliore trovata e quella ottima (fornita) : %f%  \n\n", gap);

		fprintf(resultFile,"\n\nTempo di esecuzione medio : %f", elapsedSecs/cycles);

		fprintf(resultFile,"\n\n");

		fprintf(resultFile,"Fine\n");

		fclose(resultFile);

		printf("\n\nRisultato salvato in 'result.txt'\n");
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


	int ClarkeWright::calculateFO(map<int, route_data*> routes, ProblemData problemData)
	{
		route_data* routeData;
		vector<int> route;
		vector<vector<int> > edgeWeightSection = problemData.getEdgeWeightSection();
		int fo=0;

		for(map<int, route_data*>::iterator it = routes.begin(); it != routes.end(); ++it)
		{
			routeData = routes[it->first];
			route=routeData->route;

			for(size_t i=0; i< route.size() -1; i++)
			{
				fo+=edgeWeightSection[route[i]][route[i+1]];
			}
		}

		return fo;
	}

	void ClarkeWright::printRoutes(map<int, route_data*> routes, ProblemData problemData, FILE * resultFile)
	{
		route_data* routeData;
		vector<int> route;
		vector<vector<int> > edgeWeightSection = problemData.getEdgeWeightSection();
		map<int, int> demandSection = problemData.getDemandSection();

		int routeWeight;
		int routeCapacity;

		fprintf(resultFile, "\nSoluzione trovata:\n");
		for(map<int, route_data*>::iterator it = routes.begin(); it != routes.end(); ++it)
		{
			routeWeight=0;
			routeCapacity=0;
			routeData = routes[it->first];
			route=routeData->route;

			fprintf(resultFile, "\nRoute n: %d\n", it->first);

			for(size_t i=0; i< route.size() -1; i++)
			{
				routeWeight+=edgeWeightSection[route[i]][route[i+1]];
				routeCapacity+=demandSection[route[i]+1];
				fprintf(resultFile, " %d -- %d (%d) \n", route[i]+1, route[i+1]+1, edgeWeightSection[route[i]][route[i+1]]);
			}
			fprintf(resultFile, "Peso route : %d\n", routeWeight);
			fprintf(resultFile, "Capacita' richiesta route : %d\n", routeCapacity);

			fprintf(resultFile, "\nFine route\n ");
		}
	}


