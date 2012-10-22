#include "TestAppState.h"
#include <memory>
#include "TestTask.h"
#include "TestTask2.h"
#include "Tasks/Kernel.h"

TestAppState::TestAppState(void) {}

TestAppState::~TestAppState(void) {}

bool TestAppState::start() {
	t1 = std::make_shared<TestTask>();
	t1->setPriority(*this, -40);
	t2 = std::make_shared<TestTask>();
	t2->setPriority(*this, -20);
	t3 = std::make_shared<TestTask>();
	t3->setPriority(*this, 20);
	t4 = std::make_shared<TestTask>();
	t4->setPriority(*this, 40);

	Kernel::getInstance()->addTask(t1);
	Kernel::getInstance()->addTask(t2);
	Kernel::getInstance()->addTask(t3);
	Kernel::getInstance()->addTask(t4);
	return true;
}

void TestAppState::update() {
	TestTask2::report(getPriority());
}

void TestAppState::stop() {
	t1->canKill = true;
	t2->canKill = true;
	t3->canKill = true;
	t4->canKill = true;
}