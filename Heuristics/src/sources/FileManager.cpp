/*
 * FileManager.cpp
 *
 *  Created on: Sep 20, 2014
 *      Author: alex
 */

#include "../headers/FileManager.h"



	string FileManager::getDataPath()
	{
		string path = getProjectPath();
		path.append("/data/");

		return path;
	}

	string FileManager::getFileContent(string filePath)
	{
		ifstream fileReader;
		char *contents;
		int size;

		fileReader.open(filePath.c_str(), ios::out | ios::ate | ios::binary);

		if(fileReader.is_open())
		{
			fileReader.seekg(0, ios::end);
			size = fileReader.tellg();
			contents = new char [size];
			fileReader.seekg (0, ios::beg);
			fileReader.read (contents, size);
			fileReader.close();
		}

		return contents;
	}

	string FileManager::getProjectPath()
	{
		char cCurrentPath[FILENAME_MAX];

		if (!GetCurrentDir(cCurrentPath, sizeof(cCurrentPath)))
		{
			return "error";
		}

		cCurrentPath[sizeof(cCurrentPath) - 1] = '\0';

		return cCurrentPath;
	}
