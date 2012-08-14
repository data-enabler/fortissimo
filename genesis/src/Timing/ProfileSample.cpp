#include "ProfileSample.h"
#include <allegro5/allegro.h>
#include <cassert>
#include "float.h"
#include "ProfilerLogHandler.h"

#define _CRT_SECURE_NO_WARNINGS

int ProfileSample::lastOpenedSample = -1;
int ProfileSample::openSampleCount = 0;
double ProfileSample::rootBegin;
double ProfileSample::rootEnd;
ProfileSample::PSample ProfileSample::samples[];
ProfilerOutputHandler* ProfileSample::outputHandler = new ProfilerLogHandler();

ProfileSample::ProfileSample(std::string sampleName)
{
	int storeIndex = -1;

	// Find a valid sample with the given name,
	// or create one using the first non-valid index
	for (int i = 0; i < MAX_PROFILER_SAMPLES; i++) {
		if (!samples[i].isValid) {
			if (storeIndex < 0) storeIndex = i;
		} else {
			if (samples[i].name == sampleName) {
				// sample found
				assert(!samples[i].isOpen && "Tried to profile a sample which was already being profiled");

				sampleIndex = i;
				parentIndex = lastOpenedSample;
				lastOpenedSample = i;
				samples[i].parentCount = openSampleCount;
				openSampleCount++;
				samples[i].isOpen = true;
				samples[i].callCount++;
				samples[i].startTime = al_get_time();

				// if this is the root sample
				if (parentIndex < 0) rootBegin = samples[i].startTime;
				return;
			}
		}
	}

	// create new sample
	assert(storeIndex >= 0 && "Profiler has run out of sample slots");
	samples[storeIndex].isValid = true;
	samples[storeIndex].name = sampleName;
	sampleIndex = storeIndex;
	parentIndex = lastOpenedSample;
	lastOpenedSample = storeIndex;
	samples[storeIndex].parentCount = openSampleCount;
	openSampleCount++;
	samples[storeIndex].isOpen = true;
	samples[storeIndex].callCount = 1;

	// init statistics for the sample
	samples[storeIndex].totalTime = 0.0;
	samples[storeIndex].childTime = 0.0;
	samples[storeIndex].startTime = al_get_time();
	if (parentIndex < 0) rootBegin = samples[storeIndex].startTime;
}

ProfileSample::~ProfileSample()
{
	double endTime = al_get_time();
	double timeTaken = endTime - samples[sampleIndex].startTime;
	samples[sampleIndex].isOpen = false;

	if (parentIndex >= 0) {
		samples[parentIndex].childTime += timeTaken;
	} else {
		rootEnd = endTime;
	}

	samples[sampleIndex].totalTime += timeTaken;
	lastOpenedSample = parentIndex;
	openSampleCount--;
}

void ProfileSample::output()
{
	assert(outputHandler && "Profiler has no output handler set");

	outputHandler->beginOutput();

	for (int i = 0; i < MAX_PROFILER_SAMPLES; i++) {
		if (samples[i].isValid) {
			double sampleTime = samples[i].totalTime - samples[i].childTime;
			float percentage = sampleTime / (rootEnd - rootBegin) * 100.0f;

			float totalPercent = samples[i].averagePercent * samples[i].dataCount;
			totalPercent += percentage;
			samples[i].dataCount++;
			samples[i].averagePercent = totalPercent / samples[i].dataCount;

			if (percentage < samples[i].minPercent) samples[i].minPercent = percentage;
			if (percentage > samples[i].maxPercent) samples[i].maxPercent = percentage;
			
			// output values
			outputHandler->addSample(samples[i].minPercent,
				samples[i].averagePercent,
				samples[i].maxPercent,
				samples[i].callCount,
				samples[i].name,
				samples[i].parentCount);

			// reset sample
			samples[i].callCount = 0;
			samples[i].totalTime = 0;
			samples[i].childTime = 0;
		}
	}

	outputHandler->endOutput();
}

void ProfileSample::resetSample(std::string sampleName)
{
	for (int i = 0; i < MAX_PROFILER_SAMPLES; i++) {
		if (samples[i].name == sampleName) {
			samples[i].isValid = false;
			samples[i].dataCount = 0;
			samples[i].averagePercent = 0.0f;
			samples[i].minPercent = FLT_MAX;
			samples[i].maxPercent = FLT_MIN;
		}
	}
}

void ProfileSample::resetAll()
{
	for (int i = 0; i < MAX_PROFILER_SAMPLES; i++) {
		samples[i].isValid = false;
		samples[i].dataCount = 0;
		samples[i].averagePercent = 0.0f;
		samples[i].minPercent = FLT_MAX;
		samples[i].maxPercent = FLT_MIN;
	}
}