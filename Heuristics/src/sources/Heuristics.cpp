//============================================================================
// Name        : Heuristics.cpp
// Author      : Alessandro Massa
// Version     :
// Copyright   : Property of Alessandro Massa
// Description : Heuristics
//============================================================================

#include "../headers/FileManager.h"
#include "../headers/DataParser.h"
#include "../headers/ProblemData.h"
#include "../headers/ClarkeWright.h"
#include <iostream>
using namespace std;

int main()
{
	int choice=0;
	ifstream fileReader;
	string filePath;
	string contents;
	ProblemData problemData;
	map<string, int> optimalSolution;
	map<int, string> choiceMap;

	choiceMap[1]="A034-02f.dat";
	choiceMap[2]="A036-03f.dat";
	choiceMap[3]="A039-03f.dat";
	choiceMap[4]="A045-03f.dat";
	choiceMap[5]="A048-03f.dat";
	choiceMap[6]="A056-03f.dat";
	choiceMap[7]="A065-03f.dat";
	choiceMap[8]="A071-03f.dat";

	optimalSolution["A034-02f"]=1406;
	optimalSolution["A036-03f"]=1644;
	optimalSolution["A039-03f"]=1654;
	optimalSolution["A045-03f"]=1740;
	optimalSolution["A048-03f"]=1891;
	optimalSolution["A056-03f"]=1739;
	optimalSolution["A065-03f"]=1974;
	optimalSolution["A071-03f"]=2054;

	filePath = FileManager::getDataPath();

	printf("Scegli il problema \n1) A034-02f.dat \n2) A036-03f.dat \n3) A039-03f.dat \n4) A045-03f.dat \n5) A048-03f.dat \n6) A056-03f.dat \n7) A065-03f.dat \n8) A071-03f.dat \nScelta : ");

	cin >> choice;

	if(choice>choiceMap.size() || choice<1)
		choice=1;

	filePath.append(choiceMap[choice]);
	contents = FileManager::getFileContent(filePath);


	problemData = DataParser::parseData(contents);
	problemData.setOptimalSolution(optimalSolution);

	ClarkeWright::solve(problemData);

	return 0;
}
