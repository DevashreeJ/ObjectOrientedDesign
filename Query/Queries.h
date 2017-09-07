///////////////////////////////////////////////////////////////////////
// Queries.h - firing queries on db created by nosql object			 //
// Application: Creating Nosql db for storing and retrieving data    //
// Platform:    Lenovo, Win 10, Visual Studio 2015		             //
// Author:	    Devashree Jadhav                                     //
// CSE687 -    Object Oriented Design, Spring 2017					 //
///////////////////////////////////////////////////////////////////////
/*
* Package Operations:
* -------------------
* This Package creates queries to be fired on the database created by Nosql package .
* The Query class is uses an object of NoSqlDb class and performs operations on the 
* populated elements.
*
* Query class :
* Consists of nosqldb object to perform operations on it. Uses this object and 
* iterates on the map to extract information matching specific criteria.
* The data variable might be any kind of data ranging from string to struct.
* 
*
* Member functions:
* childrenOfKey() - displays the children of elements pf specified list of keys.
* patternInKey () - displays the keys with specific pattern in their string. Returns this vector of found keys.
* valueOfKeylist()    - dislays values of all the keys sent in the vector as parameter.
* itemNamePattern() - displays values of keys having pattern in item name.
* categoryNamePattern() - returns keys with specific pattern in their category name.
* stringDataPattern() - returns keys with pattern in data section.
* displayData() - displays data of specfic key.
* saveQuery() - saves the results of fired query.
* UnionQuery() - returns combined result of two queries.
*
* Files Used : 
* -------------------
* CppProperties.h , NoSqlDb.h
*/

#pragma once
#pragma warning(disable : 4996)
#include <unordered_map>
#include<algorithm>
#include <string>
#include <sstream>
#include <vector>
#include <iomanip>
#include <regex>
#include <iostream>
#include <iterator>
#include "../NoSqlDb/NoSqlDb.h"
#include "../CppProperties/CppProperties.h"


template<typename Data>
class Query
{
public:
	NoSqlDb <Data> nosql;
	template<typename Data>
	friend class Test;

	using Key = std::string;
	using Keys = std::vector<Key>;
	std::vector<std::string>Query<Data>::childrenOfKey(std::vector<std::string> inputList);
	std::vector<std::string> Query<Data>::patternInKey(std::vector<std::string> inputList, std::string pattern);
	std::vector<std::string>Query<Data>::valueOfKeyList(std::vector<std::string> &inputList);
	std::vector<std::string>Query<Data>::itemNamePattern(std::vector<std::string> inputList, std::string pattern);
	std::vector<std::string>Query<Data>::categoryNamePattern(std::vector<std::string> inputList, std::string pattern);
	std::vector<std::string>Query<Data>::stringDataPattern(std::vector<std::string> inputList, std::string pattern);
	void Query<Data>::displayData(std::string &keyVal);
	void saveQuery(std::vector<std::string> solutionList);
	void UnionQuery(std::vector<std::string> &inputList1, std::vector<std::string> &inputList2);
};

template<typename Data>
std::vector<std::string> Query<Data>::stringDataPattern(std::vector<std::string> inputList, std::string pattern)
{
	std::vector<std::string> ans;
	auto it = nosql.store.begin();
	while (it != nosql.store.end())//iterate through the store
	{
		std::string strKey = it->first;
		Element<Data> elem = it->second;
	
			std::string stringKey = elem.data;
			if (std::find(inputList.begin(), inputList.end(), strKey) != inputList.end())
			{
				std::size_t found = stringKey.find(pattern);//check for the specified pattern
				if (found != std::string::npos)
				{
					ans.push_back(strKey);//push the item on the vector
				}
			}
			++it;
	}
	return ans;
}


template<typename Data>
void Query<Data>::saveQuery(std::vector<std::string> solutionList)
{
	//std::vector<std::string> soln = solutionList.begin();
	auto soln = solutionList.begin();
	auto mapReader = nosql.store.begin();
	while (soln != solutionList.end())
	{
		std::string strKey = mapReader->first;
		Element<Data> elem = mapReader->second;
		nosql.save(strKey, elem);
		soln++;
	}
}


template<typename Data>
void Query<Data>::UnionQuery(std::vector<std::string> &inputList1, std::vector<std::string> &inputList2)
{
	std::vector<std::string> queryResult;
	auto i1 = inputList1.begin();
	auto i2 = inputList2.begin();
	queryResult = inputList1;
	//std::cout << " set of keys having pattern 'elem' in key or having pattern 'ele' in name \n";
	while (i2 != inputList2.end())
	{
		auto q = queryResult.begin();
		if (std::find(queryResult.begin(), queryResult.end(), *i2) != queryResult.end())
			i2++;
		else
		{
			std::string final = *i2;
			queryResult.push_back(final);
		}

	}

	auto q2 = queryResult.begin();
	while (q2 != queryResult.end())
	{
		std::cout << *q2 << "\n";
		++q2;
	}

}

template<typename Data>
std::vector<std::string> Query<Data>::categoryNamePattern(std::vector<std::string> inputList, std::string pattern)
{
	std::vector<std::string> ans;
	auto it = nosql.store.begin();
	while (it != nosql.store.end())//iterate through the store
	{
		std::string strKey = it->first;
		Element<Data> elem = it->second;
		std::string stringKey = elem.category;

		if (std::find(inputList.begin(), inputList.end(), strKey) != inputList.end())
		{
			std::size_t found = stringKey.find(pattern);//check for the specified pattern
			if (found != std::string::npos)
			{
				ans.push_back(strKey);//push the item on the vector
			}
		}
		++it;
	}
	return ans;
}
template <typename Data> 
std::vector<std::string>Query<Data>::itemNamePattern(std::vector<std::string> inputList, std::string pattern)
{
	std::vector<std::string> ans;
	auto it = nosql.store.begin();
	while (it != nosql.store.end())//iterate through the store
	{
		Element<Data> elem = it->second;
		std::string stringKey = elem.name;
		std::string key = it->first;

		if (std::find(inputList.begin(), inputList.end(), key) != inputList.end())
		{
			std::size_t found = stringKey.find(pattern);//check for the specified pattern
			if (found != std::string::npos)
			{
				ans.push_back(stringKey);//push the item on the vector
			}
		}
		++it;
	}
	return ans;
}

template <typename Data>
std::vector<std::string> Query<Data>::patternInKey(std::vector<std::string> inputList, std::string pattern)
{
	std::vector<std::string> ans;
	std::vector<std::string> defaultToAllKeys;

	auto it = nosql.store.begin();
	while (it != nosql.store.end())// iterate through the store
	{
		std::string stringKey = it->first;

		if (std::find(inputList.begin(), inputList.end(), stringKey) != inputList.end())
		{
			
			defaultToAllKeys.push_back(stringKey);
			std::size_t found = stringKey.find(pattern);//check for the specified pattern
			if (found != std::string::npos)
			{
				ans.push_back(stringKey);//push the item on the vector
			}
		}
		++it;
	}

	if (!ans.empty())
		return ans;
	else
	{
		std::cout << "No keys found to match the pattern- Default to all keys\n";
		return defaultToAllKeys;
	}
}

template <typename Data>
std::vector<std::string> Query<Data>::childrenOfKey(std::vector<std::string> inputList)
{
	std::vector<std::string> childrenVectorkey;
	NoSqlDb <Data> nsdb;
	auto it = nosql.store.begin();
	while (it != nosql.store.end())//iterate through the store
	{
		Element<Data> elem = it->second;
		//std::string stringKey = elem.name;
		std::string key = it->first;
		std::cout << "\nChildren Of " << key <<":";
		auto iter = inputList.begin();
		while (iter != inputList.end())
		{		
			if (*iter == key)
			{
				nsdb.showChild(elem);
				childrenVectorkey.push_back(*iter);
			}
			++iter;
		}
		++it;
	}
	return childrenVectorkey; // All keys having children
}
template <typename Data>
std::vector<std::string> Query<Data>::valueOfKeyList(std::vector<std::string> &inputList)
{
	auto it = nosql.store.begin();
	std::vector<std::string> returnedKeys;

	auto iter = inputList.begin();
	while (iter != inputList.end())
	{

		displayData(*iter);
		returnedKeys.push_back(*iter);
		++iter;
	}
	return returnedKeys; //returning keys to use as input for second query.

}
template <typename Data>
void Query<Data>::displayData(std::string &keyVal)
{
	//auto it = nosql.store.begin();
	if (nosql.store.find(keyVal) != nosql.store.end())
	{
		std::cout << "\n\nKey\t\t" << " : " << keyVal;
		std::cout << "\nname\t\t" << " : " << nosql.value(keyVal).name;
		std::cout << "\ncategory\t" << " : " << nosql.value(keyVal).category;
		std::cout << "\ntimeDate\t" << " : " << nosql.value(keyVal).timeDate;
		std::cout << "data\t\t" << " : " << nosql.value(keyVal).data ;
		std::cout << "\ndescription\t" << " : " << nosql.value(keyVal).description;
		std::cout << "\nChildren\t "<<": ";
		if (nosql.value(keyVal).getChild().empty())
		{
			std::cout << "No child";
		}
		else
		{
			nosql.showChild(nosql.value(keyVal));
		}
		
		std::cout << "\n";
	}
	else
	{
		std::cout << "invalid key";
	}
}


