#include "ProfilerLogHandler.h"
#include "Logging/Log.h"

void ProfilerLogHandler::beginOutput()
{
	Log::get().write(Log::LOG_APP, DEFAULT_PROFILER_HEADER);
}

void ProfilerLogHandler::endOutput()
{
	Log::get().write(Log::LOG_APP, "\n");
}

void ProfilerLogHandler::addSample(float min, float avg, float max, int callCount, std::string name, int parentCount)
{
	char cMin[16], cAvg[16], cMax[16], cNum[16];
	char indentedName[256];

	sprintf(cAvg, "%5.1f", avg);
	sprintf(cMin, "%5.1f", min);
	sprintf(cMax, "%5.1f", max);
	sprintf(cNum, "%3d",   callCount);

	strcpy(indentedName, "");
	for (int i = 0; i < parentCount; i++) strcat(indentedName, "-");
	strncat(indentedName, name.c_str(), 256 - parentCount - 1);
	
	Log::get().write(Log::LOG_APP, DEFAULT_PROFILER_SAMPLE, cMin, cAvg, cMax, cNum, indentedName);
}
