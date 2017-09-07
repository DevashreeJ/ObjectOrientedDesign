
///////////////////////////////////////////////////////////////////////
// TestExec.h - Sends data to XML and retreives data from XML 	 //
// Application: Creating Nosql db for storing and retrieving data    //
// Platform:    Lenovo, Win 10, Visual Studio 2015		             //
// Author:	    Devashree Jadhav                                     //
// CSE687 -    Object Oriented Design, Spring 2017					 //
///////////////////////////////////////////////////////////////////////

/*Package Operations :
*----------------------
* TestExec.h defines functions for displaying data in a specific format. Uses
* key values passed by calling object to display specified data. Uses query object
* to fire queries on specified list of keys. The basic obectiv of TestExec is to 
* demonstrate all the functionalities imlemented in various packages.
*
* Test Class:
* This class uses objects of nosqldb to display results by keys.
*
* Member functions : 
* showAllKeys () - This method displays all the keys which are mentioned in the parameters.
*
*Files Used :
*------------------ -
*CppProperties.h, NoSqlDb.h,Convert.h, StrHelper.h,XmlDocument.h,XmlElement.h
*/

#pragma once
#pragma warning(disable:4996)
#include"../NoSqlDb/NoSqlDb.h"
#include"../Query/Queries.h"
#include <ctime>
#include <chrono>
#include <fstream>
#include "../XmlDocument/XmlDocument/XmlDocument.h"
#include "../XmlDocument/XmlElement/XmlElement.h"
#include "../CppProperties/CppProperties.h"
#include "../Convert/Convert.h"
#include "../StrHelper.h"
#include "../NoSqlDb/NoSqlDb.h"
#include "../Persistance/Persistance.h"

template<typename Data>
class Test
{
private:
	NoSqlDb <Data> nsObj;
	Element <Data> element;
	XmlPersistence<Data> persistObj;
	
public:
	Query   <Data> queryObj;
	void Test<Data>::showAllKeys(std::vector<std::string> &solutionList);
	std::string Test<Data>::projectStructure();
	
};


template<typename Data>
void Test<Data>::showAllKeys(std::vector<std::string> &solutionList)
{
	auto i = solutionList.begin();
	std::cout << "\n\nKeys matching query:";
	while (i!=solutionList.end())
	{
		std::cout << "\n"<<*i;
		i++;
	}
	std::cout << "\n";
}
template<typename Data>
std::string Test<Data>::projectStructure()
{
	std::string xml;
	XmlDocument doc;// create the xml document
	SPtr pRoot = makeTaggedElement("Project1"); 
	doc.docElement() = pRoot;//made <Record> the root

	SPtr packageElement1 = makeTaggedElement("Package"); 
	pRoot->addChild(packageElement1);
	SPtr pTextElement = makeTextElement("NoSqlDb");
	packageElement1->addChild(pTextElement);

	SPtr usingElement = makeTaggedElement("Uses"); 
	packageElement1->addChild(usingElement);
	SPtr uTextElement = makeTextElement("CppProperties");
	usingElement->addChild(uTextElement);

	SPtr packageElement2 = makeTaggedElement("Package");
	pRoot->addChild(packageElement2);
	SPtr pTextElement2 = makeTextElement("Query");
	packageElement2->addChild(pTextElement2);

	SPtr usingElement1 = makeTaggedElement("Uses");
	packageElement2->addChild(usingElement1);
	SPtr uTextElement1 = makeTextElement("CppProperties");
	usingElement1->addChild(uTextElement1);

	SPtr usingElement2 = makeTaggedElement("Uses");
	packageElement2->addChild(usingElement2);
	SPtr uTextElement2 = makeTextElement("NoSqlDb");
	usingElement2->addChild(uTextElement2);

	SPtr packageElement3 = makeTaggedElement("Package");
	pRoot->addChild(packageElement3);
	SPtr pTextElement3 = makeTextElement("Persistance");
	packageElement3->addChild(pTextElement3);

	SPtr usingElement3 = makeTaggedElement("Uses");
	packageElement3->addChild(usingElement3);
	SPtr uTextElement3 = makeTextElement("CppProperties");
	usingElement3->addChild(uTextElement3);

	SPtr usingElement4 = makeTaggedElement("Uses");
	packageElement3->addChild(usingElement4);
	SPtr uTextElement4 = makeTextElement("NoSqlDb");
	usingElement4->addChild(uTextElement4);

	SPtr packageElement4 = makeTaggedElement("Package");
	pRoot->addChild(packageElement4);
	SPtr pTextElement4 = makeTextElement("TestExec");
	packageElement4->addChild(pTextElement4);

	SPtr usingElement5 = makeTaggedElement("Uses");
	packageElement4->addChild(usingElement5);
	SPtr uTextElement5 = makeTextElement("Query");
	usingElement5->addChild(uTextElement5);

	SPtr usingElement6 = makeTaggedElement("Uses");
	packageElement4->addChild(usingElement6);
	SPtr uTextElement6 = makeTextElement("NoSqlDb");
	usingElement6->addChild(uTextElement6);

	xml = doc.toString();
	return xml;
}







