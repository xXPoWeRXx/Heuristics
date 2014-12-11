/*
 * ProblemData.h
 *
 *  Created on: Sep 25, 2014
 *      Author: alex
 */

#ifndef PROBLEMDATA_H_
#define PROBLEMDATA_H_
#include <string>
#include <vector>
#include <map>

using std::string;
using std::vector;
using std::map;

class ProblemData
{
	public:
	ProblemData()
	{
		this->dimension=0;
		this->vehicles=0;
		this->capacity=0;
		this->depotSection=0;
	}

	int getCapacity() const {
		return capacity;
	}

	void setCapacity(int capacity) {
		this->capacity = capacity;
	}

	const string& getComment() const {
		return comment;
	}

	void setComment(const string& comment) {
		this->comment = comment;
	}

	int getDimension() const {
		return dimension;
	}

	void setDimension(int dimension) {
		this->dimension = dimension;
	}

	const string& getDisplayDataType() const {
		return displayDataType;
	}

	void setDisplayDataType(const string& displayDataType) {
		this->displayDataType = displayDataType;
	}

	const string& getEdgeWeightFormat() const {
		return edgeWeightFormat;
	}

	void setEdgeWeightFormat(const string& edgeWeightFormat) {
		this->edgeWeightFormat = edgeWeightFormat;
	}

	const vector<vector<int> >& getEdgeWeightSection() const {
		return edgeWeightSection;
	}

	void setEdgeWeightSection(const vector<vector<int> >& edgeWeightSection) {
		this->edgeWeightSection = edgeWeightSection;
	}

	const string& getEdgeWeightType() const {
		return edgeWeightType;
	}

	void setEdgeWeightType(const string& edgeWeightType) {
		this->edgeWeightType = edgeWeightType;
	}

	const string& getName() const {
		return name;
	}

	void setName(const string& name) {
		this->name = name;
	}

	const string& getType() const {
		return type;
	}

	void setType(const string& type) {
		this->type = type;
	}

	int getVehicles() const {
		return vehicles;
	}

	void setVehicles(int vehicles) {
		this->vehicles = vehicles;
	}
	const map<int, int>& getDemandSection() const {
		return demandSection;
	}

	void setDemandSection(const map<int, int>& demandSection) {
		this->demandSection = demandSection;
	}

	int getDepotSection() const {
		return depotSection;
	}

	void setDepotSection(int depotSection) {
		this->depotSection = depotSection;
	}

	const map<string, int>& getOptimalSolution() const {
		return optimalSolution;
	}

	void setOptimalSolution(const map<string, int>& optimalSolution) {
		this->optimalSolution = optimalSolution;
	}
	;

	private:
	string name;
	string comment;
	string type;
	int dimension;
	string edgeWeightType;
	string edgeWeightFormat;
	string displayDataType;
	int capacity;
	int vehicles;
	vector<vector<int> > edgeWeightSection;
	map <int, int> demandSection;
	int depotSection;
	map <string, int> optimalSolution;

};



#endif /* PROBLEMDATA_H_ */
