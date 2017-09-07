///////////////////////////////////////////////////////////////////////
// Persistance.h - Sends data to XML and retreives data from XML 	 //
// Application: Creating Nosql db for storing and retrieving data    //
// Platform:    Lenovo, Win 10, Visual Studio 2015		             //
// Author:	    Devashree Jadhav                                     //
// CSE687 -    Object Oriented Design, Spring 2017					 //
///////////////////////////////////////////////////////////////////////

/*Package Operations :
*------------------ -
* This Package saves data created from nosql data into an Xml file. With another functions, 
* it extracts data from XML file and converts it into element form. 
*
* PersistXml Class:
* Uses the Element object to transfer saved data into XML file and retrieve it in 
* the element form from created Xml.
* Member functions :
* toXml()- Sends data from Db into Xml in the form of elements
* fromXml()- Retrieves data from Xml and prints on screen.
*
*Files Used :
*------------------ -
*CppProperties.h, NoSqlDb.h,Convert.h, StrHelper.h,XmlDocument.h,XmlElement.h
*/

#pragma once
#include <unordered_map>
#include <string>
#include <sstream>
#include <vector>
#include <iomanip>
#include <iostream>

#include "../XmlDocument/XmlDocument/XmlDocument.h"
#include "../XmlDocument/XmlElement/XmlElement.h"
#include "../CppProperties/CppProperties.h"
#include "../Convert/Convert.h"
#include "../StrHelper.h"
#include "../NoSqlDb/NoSqlDb.h"

using StrData = std::string;

using namespace XmlProcessing;//used because compiler does not know where the XmlDocument is
using SPtr = std::shared_ptr<AbstractXmlElement>;

template<typename Data>
class XmlPersistence
{
public:
	
	std::string toXml(Element<Data> &e);
	Element<Data> fromXml(std::string &xml);
};
template<typename Data>
std::string XmlPersistence<Data>::toXml(Element<Data> &e)
{
	std::string xml;
	XmlDocument doc;// create the xml document
	SPtr pRoot = makeTaggedElement("Record"); // We now have <Record></Record> 
	doc.docElement() = pRoot;//made <Record> the root

	SPtr keyElement = makeTaggedElement("key"); //<key></key>
	pRoot->addChild(keyElement);
	SPtr keyTextElement = makeTextElement(e.name);
	keyElement->addChild(keyTextElement);

	SPtr nameElement = makeTaggedElement("name"); //<name></name>
	pRoot->addChild(nameElement);
	SPtr nameTextElement = makeTextElement(e.name);
	nameElement->addChild(nameTextElement);

	SPtr catElement = makeTaggedElement("category");//<category></category>
	pRoot->addChild(catElement);
	SPtr catTextElement = makeTextElement(e.category);
	catElement->addChild(catTextElement);

	SPtr descElement = makeTaggedElement("description");//<description></description>
	pRoot->addChild(descElement);
	SPtr descTextElement = makeTextElement(e.description);
	descElement->addChild(descTextElement);

	SPtr dataElement = makeTaggedElement("data");//<data></data>
	pRoot->addChild(dataElement);
	SPtr dataTextElement = makeTextElement(e.data);
	dataElement->addChild(dataTextElement);

	SPtr timeElement = makeTaggedElement("timeDate");//<timeDate></timeDate>
	pRoot->addChild(timeElement);
	SPtr timeTextElement = makeTextElement(e.timeDate);
	timeElement->addChild(timeTextElement);


	SPtr childElement = makeTaggedElement("children");//<children><children>
	pRoot->addChild(childElement);
	std::vector<std::string> output = e.getChild();
	std::vector<std::string>::iterator i;
	for (i = output.begin(); i != output.end(); ++i)
	{
		SPtr childKey = makeTaggedElement("childKey");//<key></key>
		childElement->addChild(childKey);

		std::string s = *i;
		SPtr childTextElem = makeTextElement(s);
		childKey->addChild(childTextElem);
	}

	xml = doc.toString();
	return xml;
}

template<typename Data>
Element<Data> XmlPersistence<Data>::fromXml(std::string &xml)
{
	Element<Data> e;
	XmlDocument doc(xml, XmlDocument::str);
	try
	{
		//Fetching the strings from XML
		std::vector<SPtr> desc = doc.descendents("name").select();
		std::string name_value = desc[0]->children()[0]->value();
		name_value = trim(name_value);
		e.name = name_value;

		std::vector<SPtr> desc1 = doc.descendents("category").select();
		std::string name_value1 = desc1[0]->children()[0]->value();
		name_value1 = trim(name_value1);
		e.category = name_value1;

		std::vector<SPtr> desc2 = doc.descendents("description").select();
		std::string name_value2 = desc2[0]->children()[0]->value();
		name_value2 = trim(name_value2);
		e.description = name_value2;

		std::vector<SPtr> desc3 = doc.descendents("data").select();
		std::string name_value3 = desc3[0]->children()[0]->value();
		name_value3 = trim(name_value3);
		e.data = name_value3;

		std::vector<SPtr> desc5 = doc.descendents("timeDate").select();
		std::string name_value5 = desc5[0]->children()[0]->value();
		name_value5 = trim(name_value5);
		e.timeDate = name_value5;

		int i = 0;
		std::vector<SPtr> desc4 = doc.descendents("childKey").select();
		if (!desc4.empty())
		{
			while (i<desc4.size())
			{
				std::string name_value4 = desc4[i]->children()[0]->value();
				name_value4 = trim(name_value4);
				e.setChild(name_value4);
				i++;
			}
		}

	}
	catch (const std::exception& ex)
	{
		std::cout << "some exception occurred!";
		std::cout << "\n" << ex.what();
	}
	return e;
}

int main();

