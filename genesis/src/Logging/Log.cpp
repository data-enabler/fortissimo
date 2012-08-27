#include "Log.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <cstdarg>
#include <iostream>
#include "constants.h"

using namespace std;

Log::Log() {}

Log& Log::get()
{
	static Log log;
	return log;
}

bool Log::init()
{
	if (!al_make_directory("Log")) return false;
	
	appLog.open("Log/app.log");
	clientLog.open("Log/client.log");
	serverLog.open("Log/server.log");

	if (!loadStrings()) return false;

	return true;
}

void Log::write(int target, const char* msg, ...)
{
	va_list args;
	va_start(args, msg);
	char msgBuf[1024];
	if (vsnprintf(msgBuf, 1024, msg, args) < 0) msgBuf[1023] = '\0';

	if (target & LOG_APP) {
		appLog<<msgBuf<<"\n";
#ifdef DEBUG
		appLog.flush();
#endif
	}

	if (target & LOG_CLIENT) {
		clientLog<<msgBuf<<"\n";
#ifdef DEBUG
		clientLog.flush();
#endif
	}

	if (target & LOG_SERVER) {
		serverLog<<msgBuf<<"\n";
#ifdef DEBUG
		serverLog.flush();
#endif
	}

	if (target & LOG_USER) {
		al_show_native_message_box(0, ENGINE_NAME, "Message:", msgBuf, 0, ALLEGRO_MESSAGEBOX_WARN);
	}
}

void Log::write(int target, unsigned long msgID, ...)
{
	va_list args;
	va_start(args, msgID);
	char msgBuf[1024];

	if (vsnprintf(msgBuf, 1024, logStrings[msgID - 1].c_str(), args) < 0) msgBuf[1023] = '\0';

	write(target, msgBuf);
}

void Log::write(char* const target, const char* msg, ...)
{
	va_list args;
	va_start(args, msg);
	char msgBuf[1024];
	ofstream* customLog;
	if (vsnprintf(msgBuf, 1024, msg, args) < 0) msgBuf[1023] = '\0';
	
	if (runtimeLogs.count(target)) {
		customLog = runtimeLogs.find(target)->second;
	}
	else {
		string path = "Log/";
		path += target;
		path += ".log";
		customLog = new ofstream();
		(*customLog).open(path);
		runtimeLogs.insert(pair<char*, ofstream*>(target, customLog));
	}

	(*customLog)<<msgBuf<<"\n";
#ifdef DEBUG
	(*customLog).flush();
#endif
}

bool Log::loadStrings()
{
	ifstream in("Log/logStrings.txt");
	if (in.fail()) return false;
	
	for (int i = 0; (!in.eof() && i < MAX_LOG_STRINGS); i++) {
		char msgBuf[1024];
		in.getline(msgBuf, 1024);
		logStrings[i] = msgBuf;
	}
	
	return true;
}