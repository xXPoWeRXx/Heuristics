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

using namespace std;

int main()
{
	ifstream fileReader;
	string filePath;
	string contents;
	ProblemData problemData;
	map<string, int> optimalSolution;
	optimalSolution["A034-02f"]=1406;
	optimalSolution["A036-03f"]=1644;
	optimalSolution["A039-03f"]=1654;
	optimalSolution["A045-03f"]=1740;
	optimalSolution["A048-03f"]=1891;
	optimalSolution["A056-03f"]=1739;
	optimalSolution["A065-03f"]=1974;
	optimalSolution["A071-03f"]=2054;

	filePath = FileManager::getDataPath();
	filePath.append("A034-02f.dat");
	contents = FileManager::getFileContent(filePath);

	problemData = DataParser::parseData(contents);
	problemData.setOptimalSolution(optimalSolution);

	ClarkeWright::solve(problemData);

	return 0;
}
