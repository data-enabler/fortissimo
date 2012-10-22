#pragma once
#include <limits>
#include <memory>
#include <string>
#include "ProfilerOutputHandler.h"
#ifdef min
#undef min
#endif
#ifdef max
#undef max
#endif 

class ProfileSample
{
protected:
	static const int MAX_PROFILER_SAMPLES = 256;
	// index into the array of samples
	int sampleIndex;
	int parentIndex;

	static struct PSample
	{
		bool isValid;
		bool isOpen;
		unsigned int callCount;
		std::string name;

		double startTime; // in seconds
		double totalTime; // total time recorded across all executions of this sample
		double childTime; // total time taken by children of this sample

		int parentCount;

		double averagePercent;	// average percentage of game loop time taken up
		double minPercent;		// maximum percentage of game loop time taken up
		double maxPercent;		// minimum percentage of game loop time taken up
		unsigned long dataCount; // number of times values have been stored
		
		PSample()
		{
			isValid = false; // initialise the next time we use this
			dataCount = 0;
			averagePercent = 0.0f;
			minPercent = std::numeric_limits<float>::max();
			maxPercent = std::numeric_limits<float>::min();
		}
	} samples[MAX_PROFILER_SAMPLES];

	static int lastOpenedSample;
	static int openSampleCount;
	static double rootBegin, rootEnd;
	
public:
	ProfileSample(std::string sampleName);
	~ProfileSample();

	static void output();

	static void resetSample(std::string sampleName);
	static void resetAll();

	static std::shared_ptr<ProfilerOutputHandler> outputHandler;
};