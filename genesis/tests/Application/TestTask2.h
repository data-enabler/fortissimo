#pragma once
#include "Tasks\Task.h"
#include <memory>
#include "TestAppState.h"

class TestTask2 : public Task
{
private:
	static short prevPriority;
	std::shared_ptr<Task> state1;
	std::shared_ptr<Task> state2;
	int tickCount;

public:
	TestTask2(void);
	~TestTask2(void);

	bool start();
	void update();
	void stop();

	static void report(short priority);
};