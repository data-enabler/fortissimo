#include "SettingsManager.h"
#include <algorithm>
#include <cctype>
#include <fstream>
#include <list>
#include <sstream>
#include "Tools/StringManip.h"
#include "ListDator.h"

#define BUF_SIZE 1024

SettingsManager::SettingsManager()
{
	settingMap.clear();
}

SettingsManager::~SettingsManager()
{

}

void SettingsManager::registerVariable(std::string& name, std::shared_ptr<BaseDator> var)
{
	settingMap[name] = var;
}

void SettingsManager::registerVariable(char* name, std::shared_ptr<BaseDator> var)
{
	settingMap[std::string(name)] = var;
}

void SettingsManager::setVariable(std::string& name, std::string& value, int bias, bool modifiable)
{
	if (!settingMap[name]) return; //setting not registered

	if (settingMap[name]->hasMultipleValues()) {
		std::list<std::string> valueList;
		valueList.clear();

		StringManip::split(value, valueList, ';');

		//clear if bias = 0
		std::list<std::string>::iterator it = valueList.begin();
		if (bias > 0) {
			(*settingMap[name]) += (*it);
		} else if (bias < 0) {
			(*settingMap[name]) -= (*it);
		} else {
			(*settingMap[name]) = (*it);
		}
		it++;

		for (; it != valueList.end(); it++) {
			if (bias >= 0) {
				(*settingMap[name]) += (*it);
			} else {
				(*settingMap[name]) -= (*it);
			}
		}
	} else {
		(*settingMap[name]) = value;
	}
}

void SettingsManager::parseSetting(std::string str)
{
	int bias = 0;
	bool modifiable = false;
	std::string name, value;
	
	//remove whitespace
	trimWhitespace(str, '"');

	//check if setting is runtime-modifiable
	if (str[0] == '%') {
		modifiable = true;
		str = str.substr(1);
	}

	//check for bias
	if ((str[0] == '+') || (str[0] == '-')) {
		bias = (str[0] == '+') * 2 - 1; // + maps to 1, - maps to -1
		str = str.substr(1);
	}

	int eqPos = str.find('=');
	if (eqPos != std::string::npos) {
		//split around = sign
		name = str.substr(0, eqPos);
		value = str.substr(eqPos + 1);
	} else {
		name = str;
		std::ostringstream convert;
		convert << (bias + 2) / 2;
		value =  convert.str();
	}

	setVariable(name, value, bias, modifiable);
}

void SettingsManager::parseFile(std::string filename)
{
	std::ifstream in("Config/" + filename);
	if (in.fail()) return;

	while (!in.eof()) {
		char buf[BUF_SIZE];
		in.getline(buf, BUF_SIZE);
		parseSetting(buf);
	}
}

//removes whitespace, but ignores sections surrounded by the specified escape character
void SettingsManager::trimWhitespace(std::string& str, char escape)
{
	int eqPos = str.find('=');
	if (eqPos != std::string::npos) { //not boolean
		if (str.find(';') == std::string::npos) { //single value
			int opening = str.find(escape, eqPos);
			int closing = str.rfind(escape);
			if (opening != closing) { //at least 2 quotation marks
				StringManip::removeWhitespace(str, closing, str.length());
				str.erase(closing, 1);
				str.erase(opening, 1);
				StringManip::removeWhitespace(str, 0, opening);
			} else {
				StringManip::removeWhitespace(str);
			}
		} else { //multiple values
			int separator1 = str.rfind(';');
			int separator2 = str.length();
			
			while (separator1 != std::string::npos) { //
				int opening = str.find(escape, separator1);
				int closing = str.rfind(escape, separator2);

				if (opening != closing) {
					StringManip::removeWhitespace(str, closing, separator2);
					str.erase(closing, 1);
					str.erase(opening, 1);
					StringManip::removeWhitespace(str, separator1, opening);
				} else {
					StringManip::removeWhitespace(str, separator1, separator2);
				}

				separator2 = separator1;
				separator1 = str.rfind(';', separator2 - 1);
				if (separator1 == std::string::npos) separator1 = str.rfind('=', separator2 - 1);
			}

			StringManip::removeWhitespace(str, 0, separator2);
		}
	} else { //boolean
		StringManip::removeWhitespace(str);
	}
}