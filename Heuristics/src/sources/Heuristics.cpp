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
#include "../headers/ProblemSolver.h"

using namespace std;

int main()
{
	ifstream fileReader;
	string filePath;
	string contents;
	ProblemData problemData;

	filePath = FileManager::getDataPath();
	filePath.append("A034-02f.dat");
	contents = FileManager::getFileContent(filePath);

	problemData = DataParser::parseData(contents);

	ProblemSolver::solve(problemData);

//	vector<int> prova1;
//	prova1.push_back(1);
//	prova1.push_back(2);
//	vector<int> prova2;
//	prova2.push_back(3);
//	prova2.push_back(4);
//	prova1.insert(prova1.end(),prova2.begin(), prova2.end());
//	prova1.push_back(5);
//
//	for(size_t i=0; i < prova1.size(); i++)
//	{
//		printf("\n %d", prova1[i]);
//	}

	return 0;
}
