#include "TestTask2.h"
#include <limits>
#include "ApplicationTest.h"
#include "TestAppState.h"
#include "Tasks/Kernel.h"

short TestTask2::prevPriority;

TestTask2::TestTask2(void) {
	tickCount = 0;
}

TestTask2::~TestTask2(void) {}

bool TestTask2::start() {
	priority = std::numeric_limits<short>::max();

	state1 = std::make_shared<TestAppState>();
	state1->setPriority(0);
	state2 = std::make_shared<TestAppState>();
	state2->setPriority(30);

	Kernel::getInstance()->addTask(state1);
	Kernel::getInstance()->addTask(state2);
	return true;
}

void TestTask2::update() {
	prevPriority = std::numeric_limits<short>::max();
	if (++tickCount > 3) {
		canKill = true;
		state1->canKill = true;
		state2->canKill = true;
	}
}

void TestTask2::stop() {}

void TestTask2::report(short priority) {
	if (priority > prevPriority) ApplicationTest::failFlag = true;
	prevPriority = priority;
}