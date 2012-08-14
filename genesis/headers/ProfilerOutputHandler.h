#pragma once
#include <string>

#define DEFAULT_PROFILER_HEADER "   Min |   Avg |   Max |   # | Profile Name\n---------------------------------------------"
#define DEFAULT_PROFILER_SAMPLE " %s | % s | %s | %s | %s"

class ProfilerOutputHandler
{
public:
	virtual void beginOutput() = 0;
	virtual void addSample(float min, float avg, float max, int callCount, std::string name, int parentCount) = 0;
	virtual void endOutput() = 0;
};