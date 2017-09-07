/////////////////////////////////////////////////////////////////////
// NoSqlDb.cpp - key/value pair in-memory database                 //
//                                                                 //
// Jim Fawcett, CSE687 - Object Oriented Design, Spring 2017       //
/////////////////////////////////////////////////////////////////////
#pragma warning(disable : 4996)
#include "NoSqlDb.h"
#include <iostream>
#include<ctime>
#include<chrono>
using StrData = std::string;
using intData = int;
using Key = NoSqlDb<StrData>::Key;
using Keys = NoSqlDb<StrData>::Keys;

int main()
{
	std::cout << "\n  Demonstrating NoSql Helper Code";
	std::cout << "\n =================================\n";

	std::cout << "\n  Creating and saving NoSqlDb elements with string data";
	std::cout << "\n -------------------------------------------------------\n";

	time_t now = time(0);
	char * dt = ctime(&now);
	NoSqlDb<StrData> db;

	Element<StrData> elem1;
	elem1.name = "elem1";
	elem1.category = "test";
	elem1.data = "elem1's StrData";
	elem1.timeDate = dt;
	db.save(elem1.name, elem1);


	Element<StrData> elem2;
	elem2.name = "elem2";
	elem2.category = "test";
	elem2.data = "elem2's StrData";
	elem2.timeDate = dt;
	elem2.setChild(elem1.name);
	db.save(elem2.name, elem2);


	Element<StrData> elem3;
	elem3.name = "elem3";
	elem3.category = "test";
	elem3.data = "elem3's StrData";
	elem3.timeDate = dt;
	elem3.setChild("elem2");
	elem3.setChild(elem1.name);
	db.save(elem3.name, elem3);

	
	std::cout << "\n \n  element before removing and updating";
	std::cout << "\n  Retrieving elements from NoSqlDb<string>";
	std::cout << "\n ------------------------------------------\n";

	std::cout << "\n  size of db = " << db.count() << "\n";
	Keys keys = db.keys();
	for (Key key : keys)
	{
		std::cout << "\n  " << key << ":";
		std::cout << db.value(key).show();
		std::cout <<  "\n    children" << ":";
		if (db.value(key).getChild().empty())
		{
			std::cout << "No child";
		}
		else
		{
			db.showChild(db.value(key));
		}
		std::cout << "\n\n";

	}

	elem3.removeChild("elem2");    // removing elem2 from child list of elem1
	db.updateData(elem3.name, elem3);


	Element<StrData> elemToUpdate;
	elemToUpdate.name = elem2.name;
	elemToUpdate.category = "testingUpdate";
	elemToUpdate.data = "Testing update functionality";
	elemToUpdate.description = "newElems updated version";
	elemToUpdate.timeDate = dt;
	db.updateData(elem2.name, elemToUpdate); // performing update operation without changing name of element.

	db.deleteElement(elem1);  //deleting elem1 from map
	

	
	Keys keys2 = db.keys();
	std::cout << "\n\n  Retrieving elements from NoSqlDb<string> after modifications";
	std::cout << "\n ------------------------------------------\n";
	std::cout << "\n element after updating and removing";
	std::cout << "\n performed the following changes: ";
	std::cout << "\n 1.Removed elem2 from children of elem3 ";
	std::cout << "\n 2.Deleted elem1 from db : this causes elem1 to get deleted as child from elem3 and elem2 list\n ";

	std::cout << "\n  size of db = " << db.count() << "\n";

	for (Key key : keys2)
	{
		
		std::cout << "\n  " << key << ":";
		std::cout << db.value(key).show();
		std::cout << "\n    children" << ":";
		if (db.value(key).getChild().empty())
		{
			std::cout << "No child";
		}
		else
		{
			db.showChild(db.value(key));
		}
		std::cout << "\n\n";
	}
	std::cout << "\n";
}

 /* std::cout << "\n  Creating and saving NoSqlDb elements with int data";
  std::cout << "\n ----------------------------------------------------\n";

  NoSqlDb<intData> idb;

  Element<intData> ielem1;
  ielem1.name = "elem1";
  ielem1.category = "test";
  ielem1.data = 1;

  idb.save(ielem1.name, ielem1);

  Element<intData> ielem2;
  ielem2.name = "elem2";
  ielem2.category = "test";
  ielem2.data = 2;

  idb.save(ielem2.name, ielem2);

  Element<intData> ielem3;
  ielem3.name = "elem3";
  ielem3.category = "test";
  ielem3.data = 3;

  idb.save(ielem3.name, ielem3);

  Element<intData> ielem4;
  ielem3.name = "elem4";
  ielem3.category = "test";
  ielem3.data = 4;

  idb.save(ielem3.name, ielem3);

  std::cout << "\n  Retrieving elements from NoSqlDb<int>";
  std::cout << "\n ---------------------------------------\n";

  std::cout << "\n  size of idb = " << idb.count() << "\n";
  Keys ikeys = idb.keys();
  for (Key key : ikeys)
  {
    std::cout << "\n  " << key << ":";
    std::cout << idb.value(key).show();

  }
  std::cout << "\n\n";
}*/