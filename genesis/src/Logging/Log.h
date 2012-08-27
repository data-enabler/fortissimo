#pragma once
#include <fstream>
#include <map>

#define MAX_LOG_STRINGS 256

class Log
{
protected:
	Log();

	std::ofstream appLog;
	std::ofstream clientLog;
	std::ofstream serverLog;

	std::map<char*, std::ofstream*> runtimeLogs;

	std::string logStrings[MAX_LOG_STRINGS];
	bool loadStrings();

public:
	static const int LOG_APP = 1;
	static const int LOG_CLIENT = 2;
	static const int LOG_SERVER = 4;
	// Display error to user
	static const int LOG_USER = 8;
	
	static Log& get();

	bool init();
	void write(int target, const char* msg, ...);
	void write(int target, unsigned long msgID, ...);
	void write(char* const target, const char* msg, ...);
};