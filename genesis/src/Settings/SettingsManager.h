#pragma once
#include "Utilities/Singleton.h"
#include <map>
#include <string>
#include "BaseDator.h"
#include "Memory/MMPointer.h"

class SettingsManager : public Singleton<SettingsManager>
{
protected:
	std::map<std::string, BaseDator*> settingMap;

public:
	SettingsManager();
	virtual ~SettingsManager();

	void registerVariable(std::string& name, BaseDator* var);
	void registerVariable(char* name, BaseDator* var);
	void setVariable(std::string& name, std::string& value, int bias = 0, bool modifiable = false);

	void parseSetting(std::string str);
	void parseFile(std::string filename);
	
	void trimWhitespace(std::string& str, char escape = '"');
};
