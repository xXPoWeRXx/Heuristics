//============================================================================
// Name        : Heuristics.cpp
// Author      : Alessandro Massa
// Version     :
// Copyright   : Copyright
// Description : Hello World in C++, Ansi-style
//============================================================================

#include "../headers/FileManager.h"
#include "../headers/DataParser.h"

using namespace std;

int main()
{
	ifstream fileReader;
	string filePath;
	string contents;

	filePath = FileManager::getDataPath();
	filePath.append("A034-02f.dat");
	contents = FileManager::getFileContent(filePath);

	DataParser::parseData(contents);

	return 0;
}
