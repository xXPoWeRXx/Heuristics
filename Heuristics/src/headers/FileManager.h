/*
 * FileManager.h
 *
 *  Created on: Sep 20, 2014
 *      Author: alex
 */


#ifndef FILEMANAGER_H_
#define FILEMANAGER_H_

#include <string>
#include <fstream>
#include <sstream>
#ifdef WINDOWS
    #include <direct.h>
    #define GetCurrentDir _getcwd
#else
    #include <unistd.h>
    #define GetCurrentDir getcwd
 #endif

using std::string;
using std::stringstream;
using std::ifstream;
using std::ios;


class FileManager
{
	public :
	FileManager(){};
	static string getDataPath();
	static string getFileContent(string filePath);
	static string getFilePath(string fileName);

	private:
	static string getProjectPath();

};




#endif /* FILEMANAGER_H_ */
