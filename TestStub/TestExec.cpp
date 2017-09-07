///////////////////////////////////////////////////////////////////////
// TestExec.cpp - Demonstration of requirements that have been met 	 //
// Application: Creating Nosql db for storing and retrieving data    //
// Platform:    Lenovo, Win 10, Visual Studio 2015		             //
// Author:	    Devashree Jadhav                                     //
// CSE687 - Object Oriented Design, Spring 2017		                 //
///////////////////////////////////////////////////////////////////////


#pragma warning(disable : 4996)
#include "../NoSqlDb/NoSqlDb.h"
#include"TestExec.h"
#include <iostream>
#include<ctime>
#include <typeinfo>
#include<chrono>
#include"../Query/Queries.h"
using StrData = std::string;
using intData = int;
using Key = NoSqlDb<StrData>::Key;
using Keys = NoSqlDb<StrData>::Keys;

int main()
{
	std::cout << "\n  Demonstrating Project 1 - OOD Spring 2017";
	std::cout << "\n =================================\n";

	int temp = 2;
	Query<StrData> queryObject;
	time_t now = time(0);
	char * dt = ctime(&now);
	std::vector<std::string> resultSet;
	//time(&tmval);
	NoSqlDb<StrData>db;
	Test <StrData> testObj;
	Element<StrData> elem1;
	XmlPersistence<StrData> persist;
	elem1.name = "elem1";
	elem1.category = "test";
	elem1.data = "elem1's StrData";
	elem1.timeDate = dt;
	elem1.description = "First element of db";
	testObj.queryObj.nosql.save(elem1.name, elem1);
	resultSet.push_back(elem1.name);


	Element<StrData> elem2;
	elem2.name = "elem2";
	elem2.category = "test";
	elem2.data = "elem2's StrData";
	elem2.timeDate = dt;
	elem2.description = "Second element of db";
	elem2.setChild(elem1.name); //Requirement 4-------------------Adding relationships----------------
	testObj.queryObj.nosql.save(elem2.name, elem2);
	resultSet.push_back(elem2.name);

	Element<StrData> elem3;
	elem3.name = "elem3";
	elem3.category = "test";
	elem3.data = "elem3's StrData";
	elem3.timeDate = dt;
	elem3.description = "Third element of db";
	elem3.setChild(elem2.name);
	elem3.setChild(elem1.name);
	testObj.queryObj.nosql.save(elem3.name, elem3);
	resultSet.push_back(elem3.name);

	Element<StrData> elem4;
	elem4.name = "elem4";
	elem4.category = "test";
	elem4.data = "elem4's StrData";
	elem4.timeDate = dt;
	elem4.description = "Fourth element of db";
	elem4.setChild(elem2.name);
	elem4.setChild(elem3.name);
	testObj.queryObj.nosql.save(elem4.name, elem4);
	resultSet.push_back(elem4.name);
	
	elem2.setChild(elem4.name);
	testObj.queryObj.nosql.updateData(elem2.name, elem2);
	
	std::cout << "---------------------Created elements--------------------\n";
	testObj.queryObj.valueOfKeyList(resultSet);

	//Requirement 5
	//on command, persist database contents to an XML file2. It is intended that this process be reversible, 
	//e.g., the database can be restored or augmented3 from an existing XML file as well as write its contents 
	//out to an XML file.
	//testObj.persistToXml();

	//Requirement 4--------------------Deleting relationships----------------------------
	std::cout << "\n\n---------------------Deleting relationships--------------------\n\n";
	elem3.removeChild(elem2.name);
	testObj.queryObj.nosql.updateData(elem3.name,elem3);
	std::string resultant = elem3.name;
	testObj.queryObj.displayData(resultant);

	////Requirement 3---------------------Deleting Element----------------------------------
	std::cout << "\n\n---------------------Deleting Element--------------------\n\n";
	testObj.queryObj.nosql.deleteElement(elem1);
	testObj.queryObj.valueOfKeyList(resultSet);
	/*The output will show 'invalid key' in place of elem1 as the resultset has 'elem1' but the
	map does not have the element in it anymore.*/
	

	//Requirement 4---------------------Editing Values---------------------------------
	std::cout << "\n\n--------------------Editing Values---------------------------\n\n";
	Element<StrData> newElementforupdating;
	newElementforupdating.name =elem2.name;
	newElementforupdating.category = "testingUpdate";
	newElementforupdating.data = "newElems updated version";
	newElementforupdating.timeDate = dt;
	newElementforupdating.description = "updated details";
	newElementforupdating.setChild(elem3.name);
	testObj.queryObj.nosql.updateData(elem2.name, newElementforupdating);
	std::string keyValue = elem2.name;
	testObj.queryObj.displayData(keyValue);
	
	//Requirement 7---------------------Queries------------------------------------
	std::cout << "\n\n--------------------Queries---------------------------\n\n";

	std::cout << "\n\n1.Displaying value of a specified key";
	Key newkey = elem3.name;
	testObj.queryObj.displayData(newkey);
	
	std::cout << "\n\n2.Displaying Children of specified keys";
	std::vector<std::string> query2 = testObj.queryObj.childrenOfKey(resultSet);
	testObj.queryObj.saveQuery(query2);
	//testObj.showAllKeys(query2);

	std::cout << "\n\n3.Displaying Keys matching pattern";
	std::vector<std::string> query3 = testObj.queryObj.patternInKey(resultSet,"lem");
	testObj.queryObj.saveQuery(query3);
	testObj.showAllKeys(query3);

	std::cout << "\n\n4.All keys containing specified pattern in item name";
	std::vector<std::string> query4 = testObj.queryObj.itemNamePattern(resultSet, "3");
	testObj.queryObj.saveQuery(query4);
	testObj.showAllKeys(query4);

	std::cout << "\n\n5.All keys containing specified pattern in category";
	std::vector<std::string> query5 = testObj.queryObj.categoryNamePattern(resultSet,"te");
	testObj.queryObj.saveQuery(query5);
	testObj.showAllKeys(query5);

	//Requirement 8
	//same kinds of queries, cited in the requirement above, on the set of keys returned by an earlier query.
	std::cout << "\n\n6.Executing query4 on results provided by query3  ";
	std::vector<std::string> mergeQuery = testObj.queryObj.itemNamePattern(query3, "ele");
	if (!mergeQuery.empty())
	{
		testObj.showAllKeys(mergeQuery);
	}

	//Requirement 9
	std::cout << "\n\n7.Union of 2 queries";
	std::cout << "\n\nDemostrating Union of query5 and query6\n";
	testObj.queryObj.UnionQuery(query4, query5);


	//std::string xmlAns = testObj.projectStructure();
	
	// Requirement 10:submitted with contents, in the form of an XML file, that 
	//describe your project's package structure and dependency relationships that 
	//can be loaded when your project is graded
	std::cout << "------------------ PROJECT STRUCTURE --------------------\n";
	std::ofstream myXmlDoc;
	myXmlDoc.open("../structure.xml");
	std::string ans = testObj.projectStructure();
	myXmlDoc << ans;
	std::cout << ans << "\n";
	std::cout << "Project structure has been loaded into structure.xml file for future reference\n";

}