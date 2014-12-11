/*
 * DataParser.h
 *
 *  Created on: Sep 20, 2014
 *      Author: alex
 */

#ifndef DATAPARSER_H_
#define DATAPARSER_H_

#include <string>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include "ProblemData.h"


using std::string;
using std::stringstream;
using std::remove_if;
using std::remove;

class DataParser
{
	public:

	DataParser(){};
	static ProblemData parseData(string data);

	private:
	static vector<string> split(const string &s, char delim);
	static vector<string> &split(const string &s, char delim, vector<string> &elems);


};





#endif /* DATAPARSER_H_ */
