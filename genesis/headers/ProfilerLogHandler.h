#pragma once
#include "ProfilerOutputHandler.h"

class ProfilerLogHandler : public ProfilerOutputHandler
{
	void beginOutput();
	void endOutput();
	void addSample(float min, float avg, float max, int callCount, std::string name, int parentCount);
};