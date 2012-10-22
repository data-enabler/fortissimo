#include "SettingsTest.h"
#include <fstream>
#include <iostream>
#include <list>
#include <string>
#include "Settings/Dator.h"
#include "Settings/SettingsManager.h"

SettingsTest::SettingsTest(void) {}

SettingsTest::~SettingsTest(void) {}

bool SettingsTest::run()
{
	std::cout << "Running Settings Test..." << std::endl;

	std::string bString = "+test_bool";
	bool bValue = true;

	std::string iString = "test_int =	 1 2 3 4 5 ";
	int iValue = 12345;

	std::string sString = "test_string =\t\tone   \" two three\"\t ";
	std::string sValue = "one two three";

	std::string lString = "test_list = \t  \"one\"  ; \t\"\"two\"\"  ; \"\" three \"\"  \t\n+test_list = \t  \"f o u \"     r  \t \t";
	std::list<std::string> lValue;
	lValue.push_back("one");
	lValue.push_back("\"two\"");
	lValue.push_back("\" three \"");
	lValue.push_back("f o u r");

	std::ofstream ofs("Config/settings_test.txt");
	ofs << bString << std::endl;
	ofs << iString << std::endl;
	ofs << sString << std::endl;
	ofs << lString << std::endl;
	ofs.close();

	bool b;
	std::shared_ptr<Dator<bool>> bDat(new Dator<bool>(b));
	SettingsManager::getInstance()->registerVariable("test_bool", bDat);

	int i;
	std::shared_ptr<Dator<int>> iDat(new Dator<int>(i));
	SettingsManager::getInstance()->registerVariable("test_int", iDat);

	std::string s;
	std::shared_ptr<Dator<std::string>> sDat(new Dator<std::string>(s));
	SettingsManager::getInstance()->registerVariable("test_string", sDat);

	std::list<std::string> l;
	std::shared_ptr<ListDator<std::string>> lDat(new ListDator<std::string>(l));
	SettingsManager::getInstance()->registerVariable("test_list", lDat);

	SettingsManager::getInstance()->parseFile("settings_test.txt");

	if (b != bValue) {std::cout << "Error: expected " << bValue << ", got " << b << std::endl; return false;}
	if (i != iValue) {std::cout << "Error: expected " << iValue << ", got " << i << std::endl; return false;}
	if (s != sValue) {std::cout << "Error: expected " << sValue << ", got " << s << std::endl; return false;}
	if (l != lValue) {
		std::cout << "Error: expected";
		for (std::list<std::string>::iterator it = lValue.begin(); it != lValue.end(); it++) std::cout << " " << (*it) << ";";
		std::cout << ", got";
		for (std::list<std::string>::iterator it = l.begin(); it != l.end(); it++) std::cout << " " << (*it) << ";";
		std::cout << std::endl;
		return false;
	}

	std::cout << "All tests passed." << std::endl;

	return true;
}