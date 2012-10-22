#pragma once
#include "Utilities/Singleton.h"
#include <map>
#include <memory>
#include <string>
#include "Dator.h"

class SettingsManager : public Singleton<SettingsManager>
{
protected:
	std::map<std::string, std::shared_ptr<BaseDator>> settingMap;

public:
	SettingsManager();
	virtual ~SettingsManager();

	void registerVariable(std::string& name, std::shared_ptr<BaseDator> var);
	void registerVariable(char* name, std::shared_ptr<BaseDator> var);
	void setVariable(std::string& name, std::string& value, int bias = 0, bool modifiable = false);

	void parseSetting(std::string str);
	void parseFile(std::string filename);
	
	void trimWhitespace(std::string& str, char escape = '"');
};
