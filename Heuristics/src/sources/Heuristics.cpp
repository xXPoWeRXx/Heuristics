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

	return 0;
}
