///////////////////////////////////////////////////////////////////////
// Query.cpp - key/value pair in-memory database					 //
// Application: Creating Nosql db for storing and retrieving data    //
// Platform:    Lenovo, Win 10, Visual Studio 2015		             //
// Author:	    Devashree Jadhav                                     //
// CSE687 - Object Oriented Design, Spring 2017		                 //
///////////////////////////////////////////////////////////////////////

#pragma warning(disable : 4996)
#include "Queries.h"
#include<iostream>
using Stringvalue = std::string;

int main()
{
	Query <Stringvalue> query;

	std::cout << "\n  Demonstrating NoSql Helper Code";
	std::cout << "\n =================================\n";

	std::cout << "\n  Creating and saving NoSqlDb elements with string data";
	std::cout << "\n -------------------------------------------------------\n";

	Element<Stringvalue> elem1;
	elem1.name = "elem1";
	elem1.category = "test";
	elem1.data = "elem1's StrData";
	time_t current = time(0);
	elem1.timeDate = ctime(&current);
	elem1.description = "First Element in database";
	query.nosql.save(elem1.name, elem1);


	Element<Stringvalue> elem2;
	elem2.name = "elem2";
	elem2.category = "test";
	elem2.data = "elem2's StrData";
	elem2.setChild(elem1.name);
	elem2.timeDate = ctime(&current);
	elem2.description = "Second Element in database";
	query.nosql.save(elem2.name, elem2);


	Element<Stringvalue> elem3;
	elem3.name = "elem3";
	elem3.category = "test";
	elem3.data = "elem3's StrData";
	elem3.setChild(elem2.name);
	elem3.setChild(elem1.name);
	elem3.timeDate = ctime(&current);
	elem3.description = "Second Element in database";
	query.nosql.save(elem3.name, elem3);

	std::cout << "\n  TESTING THE QUERIES>";
	std::cout << "\n ------------------------------------------\n";
	std::vector<std::string> v = { "elem1","elem2","elem3" };//test vector

	std::cout << "\n\n---- query 6: finding patterns in the template data----\n";
	std::cout << "\nPattern was found in the category of following keys:\n";
	std::vector<std::string> q6Ans = query.stringDataPattern(v, "StrData");
	query.saveQuery(q6Ans);
	if (!q6Ans.empty())
	{
		query.valueOfKeyList(q6Ans);
	}
	else
		std::cout << "No matching patterns found\n";

	std::cout << "\n\n---- query 5: finding patterns in the category name----\n";
	std::cout << "\nPattern was found in the category of following keys:\n";
	std::vector<std::string> q5Ans = query.categoryNamePattern(v, "test");
	query.saveQuery(q5Ans);
	if (!q5Ans.empty())
	{
		query.valueOfKeyList(q5Ans);
	}
	else
		std::cout << "No matching patterns found\n";

	std::cout << "\n\n---- query 4: finding patterns in the item name----\n";
	std::vector<std::string> q4Ans = query.itemNamePattern(v, "ele");
	query.saveQuery(q4Ans);
	if (!q4Ans.empty())
	{
		query.valueOfKeyList(q4Ans);
	}
	else
		std::cout << "No matching patterns found\n";

	std::cout << "\n\n---- query 3: finding patterns in the key----\n";
	std::vector<std::string> q3Ans = query.patternInKey(v, "elem");
	if (!q3Ans.empty())
	{
		query.valueOfKeyList(q3Ans);
	}
	query.saveQuery(q3Ans);

	std::cout << "\n---- query 2: children of specified key----\n";
	std::vector<std::string> q2Ans = query.childrenOfKey(v);
	query.saveQuery(q2Ans);

	std::cout << "\n---- query 1: value of specified key----\n";
	std::vector<std::string> e = query.valueOfKeyList(v);
	query.saveQuery(e);

	std::cout << "\n----Union of two queries-----\n";
	query.UnionQuery(q3Ans, q2Ans);     //set of keys having pattern "elem" in key or having pattern "ele" in name 

	std::cout << "\n-----Performing operation on new query with result from previous query data----\n";

	std::vector<std::string> mergeQuery = query.itemNamePattern(q4Ans, "ele");
	if (!mergeQuery.empty())
	{
		query.valueOfKeyList(mergeQuery);
	}   

}