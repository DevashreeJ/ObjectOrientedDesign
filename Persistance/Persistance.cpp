///////////////////////////////////////////////////////////////////////
//Persistance.cpp - Persists the data in the map into the xml file	 //
// Application: Creating Nosql db for storing and retrieving data    //
// Platform:    Lenovo, Win 10, Visual Studio 2015		             //
// Author:	    Devashree Jadhav                                     //
// CSE687 - Object Oriented Design, Spring 2017		                 //
///////////////////////////////////////////////////////////////////////
#pragma warning(disable:4996)
#include <ctime>
#include <chrono>
#include <fstream>
#include "../XmlDocument/XmlDocument/XmlDocument.h"
#include "../XmlDocument/XmlElement/XmlElement.h"
#include "../CppProperties/CppProperties.h"
#include "../Convert/Convert.h"
#include "../StrHelper.h"
#include "../NoSqlDb/NoSqlDb.h"
#include "Persistance.h"
int main()
{

	time_t now = time(0);
	char * dt = ctime(&now);

	using StrData = std::string;
	using Key = NoSqlDb<StrData>::Key;
	using Keys = NoSqlDb<StrData>::Keys;
	std::cout << "\n  Demonstrating Persistance Code";
	std::cout << "\n =================================\n";
	XmlPersistence<StrData> obj;
	NoSqlDb<StrData> db;
	//created element 1
	Element<StrData> elem1;
	elem1.name = "elem1";
	elem1.category = "testData";
	elem1.data = "elem1's StrData";
	elem1.description = "First Element of db";
	elem1.timeDate = dt;
	db.save(elem1.name, elem1);
	//created element 2
	Element<StrData> elem2;
	elem2.name = "elem2";
	elem2.category = "testData2";
	elem2.data = "elem2's StrData";
	elem2.description = "Second Element of db";
	elem2.timeDate = dt;
	db.save(elem2.name, elem2);
	//created element 3
	Element<StrData> elem3;
	elem3.name = "elem3";
	elem3.category = "testData3";
	elem3.data = "elem3's StrData";
	elem3.description = "Third element of db";
	elem3.timeDate = dt;
	elem3.setChild(elem1.name);
	elem3.setChild(elem2.name);
	db.save(elem3.name, elem3);
	//created element 4
	Element<StrData> elem4;
	elem4.name = "elem4";
	elem4.category = "test4";
	elem4.data = "elem4's StrData";
	elem4.description = "hello world 4";
	elem4.timeDate = dt;
	elem4.setChild(elem3.name);
	db.save(elem4.name, elem4);

	std::cout << "\n  size of db = " << db.count() << "\n\n";
	std::vector<std::string> toSaveXml;

	std::ofstream myXmlDoc;
	myXmlDoc.open("../xmlfile.xml");

	Keys keys = db.keys();
	for (Key key : keys)
	{
		Element<StrData> e = db.value(key);
		std::string ans = obj.toXml(e);
		toSaveXml.push_back(ans);
		//std::cout << ans<<"\n";
		myXmlDoc << ans;
	}
	std::cout << "\nData Successfully sent to XML file\n";
	myXmlDoc.close();

	//reading from file and printing it onto the console
	std::cout << "===========================================";
	std::cout << "\nFetching Data from XML file\n";
	std::cout << "===========================================";
	std::ifstream in("../xmlfile.xml");
	std::string line;
	std::string answer;
	while (std::getline(in, line))// will get each line till we reach the end of file
	{
		line = trim(line);
		answer += line;
		//std::cout << "CURRENT LINE===" << line << "\n";
		std::string temp = "</Record>";
		if (line.compare(temp) == 0)
		{
			//std::cout << "\nfound\n";
			//std::cout << "\nCURRENT CONTENTS OF ANSWER===" << answer << "\n\n\n";

			// contents of answer= string with one <record></record>
			// send this record to fromXml() and get the Element object 

			Element<StrData> element = obj.fromXml(answer);
			std::cout << "\n" << "Name:\t\t" << element.name << "\n";
			std::cout << "Description:\t" << element.description << "\n";
			std::cout << "Category:\t" << element.category << "\n";
			std::cout << "Data:\t\t" << element.data << "\n";
			std::cout << "Time Date:\t" << element.timeDate << "\n";
			std::cout << "Children:\t";
			db.showChild(element);
			std::cout << "\n\n";
			answer = "";
		}
	}

}