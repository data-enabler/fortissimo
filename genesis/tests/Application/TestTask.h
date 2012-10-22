#pragma once
#include "TestTask2.h"
#include "Tasks/Task.h"

class TestTask : public Task
{
	bool start() {return true;}
	void update() {TestTask2::report(getPriority());}
	void stop() {}
};