/*
 * DataParser.cpp
 *
 *  Created on: Sep 20, 2014
 *      Author: alex
 */

#include "../headers/DataParser.h"

	ProblemData DataParser::parseData(string data)
	{
		string nameLabel="NAME : ";
		string commentLabel="COMMENT : ";
		string typeLabel="TYPE : ";
		string notTypeLabel="_TYPE : ";
		string dimensionLabel="DIMENSION : ";
		string edgeWeightTypeLabel="EDGE_WEIGHT_TYPE : ";
		string edgeWeightFormatLabel="EDGE_WEIGHT_FORMAT : ";
		string displayDataTypeLabel="DISPLAY_DATA_TYPE : ";
		string capacityLabel="CAPACITY : ";
		string vehiclesLabel="VEHICLES : ";
		string edgeWeightSectionLabel="EDGE_WEIGHT_SECTION";
		string demandSectionLabel="DEMAND_SECTION";
		string depotSectionLabel="DEPOT_SECTION";

		string nameToTrim;

		vector<vector<int> > edgeWeightSection;
		vector<string> tokenSplittedHelper;
		vector<int> tokenSplittedBuff;

		int key;
		int value;
		map<int, int> demandSection;

		bool keyOrValue=false;

		vector<string> splitResult;

		ProblemData problemData;

		splitResult = split(data,'\n');

		for(size_t i = 0; i < splitResult.size(); i++)
		{
			if(splitResult[i].find(nameLabel) != string::npos)
			{
				nameToTrim=splitResult[i].substr(nameLabel.size(), splitResult[i].size() );
				nameToTrim.erase(remove(nameToTrim.begin(), nameToTrim.end(), '\r'), nameToTrim.end());
				problemData.setName(nameToTrim);
			}
			else if(splitResult[i].find(commentLabel) != string::npos)
			{
				problemData.setComment(splitResult[i].substr(commentLabel.size(), splitResult[i].size()));
			}
			else if( (splitResult[i].find(typeLabel) != string::npos) && splitResult[i].find(notTypeLabel) == string::npos )
			{
				problemData.setType(splitResult[i].substr(typeLabel.size(), splitResult[i].size()));
			}
			else if(splitResult[i].find(dimensionLabel) != string::npos)
			{
				problemData.setDimension(atoi( (splitResult[i].substr(dimensionLabel.size(), splitResult[i].size() )).c_str() ));
			}
			else if(splitResult[i].find(edgeWeightTypeLabel) != string::npos)
			{
				problemData.setEdgeWeightType(splitResult[i].substr(edgeWeightTypeLabel.size(), splitResult[i].size()));
			}
			else if(splitResult[i].find(edgeWeightFormatLabel) != string::npos)
			{
				problemData.setEdgeWeightFormat(splitResult[i].substr(edgeWeightFormatLabel.size(), splitResult[i].size()));
			}
			else if(splitResult[i].find(displayDataTypeLabel) != string::npos)
			{
				problemData.setDisplayDataType(splitResult[i].substr(displayDataTypeLabel.size(), splitResult[i].size()));
			}
			else if(splitResult[i].find(capacityLabel) != string::npos)
			{
				problemData.setCapacity(atoi( (splitResult[i].substr(capacityLabel.size(), splitResult[i].size())).c_str() ));
			}
			else if(splitResult[i].find(vehiclesLabel) != string::npos)
			{
				problemData.setVehicles(atoi( (splitResult[i].substr(vehiclesLabel.size(), splitResult[i].size())).c_str() ));
			}
			else if(splitResult[i].find(edgeWeightSectionLabel) != string::npos)
			{
				for(size_t j = i+1; j < splitResult.size(); j++)
				{
					i=j;
					if(splitResult[j].find(demandSectionLabel) != string::npos)
					{
						i--;
						break;
					}
					else
					{
						tokenSplittedHelper=split(splitResult[j], ' ');

						tokenSplittedBuff.clear();

						for(size_t k=0; k < tokenSplittedHelper.size();k++)
						{
							tokenSplittedHelper[k].erase(remove_if(tokenSplittedHelper[k].begin(), tokenSplittedHelper[k].end(), isspace), tokenSplittedHelper[k].end());

							if(!(tokenSplittedHelper[k].empty()))
							{
								tokenSplittedBuff.push_back(atoi(tokenSplittedHelper[k].c_str()));
							}
						}

						edgeWeightSection.push_back(tokenSplittedBuff);
					}

				}

				problemData.setEdgeWeightSection(edgeWeightSection);

			}
			else if(splitResult[i].find(demandSectionLabel) != string::npos)
			{
				for(size_t j = i+1; j < splitResult.size(); j++)
				{
					i=j;
					if(splitResult[j].find(depotSectionLabel) != string::npos)
					{
						i--;
						break;
					}
					else
					{
						tokenSplittedHelper=split(splitResult[j], ' ');

						for(size_t k=0; k < tokenSplittedHelper.size();k++)
						{
							tokenSplittedHelper[k].erase(remove_if(tokenSplittedHelper[k].begin(), tokenSplittedHelper[k].end(), isspace), tokenSplittedHelper[k].end());

							if(!(tokenSplittedHelper[k].empty()))
							{
								if(!keyOrValue)
								{
									keyOrValue=true;
									key=atoi(tokenSplittedHelper[k].c_str());
								}
								else
								{
									keyOrValue=false;
									value=atoi(tokenSplittedHelper[k].c_str());
									demandSection[key]=value;
									break;
								}
							}
						}
					}
				}

				problemData.setDemandSection(demandSection);

			}
			else if(splitResult[i].find(depotSectionLabel) != string::npos)
			{
				problemData.setDepotSection(atoi(splitResult[i+1].c_str()));
			}
		}

		return problemData;
	}


	vector<string> &DataParser::split(const string &s, char delim, vector<string> &elems)
	{
	    stringstream ss(s);
	    string item;

	    while (getline(ss, item, delim))
	    {
	        elems.push_back(item);
	    }

	    return elems;
	}


	vector<string> DataParser::split(const string &s, char delim)
	{
	    vector<std::string> elems;
	    split(s, delim, elems);
	    return elems;
	}
