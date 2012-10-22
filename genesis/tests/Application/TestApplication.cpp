#include "TestApplication.h"
#include <memory>
#include "TestTask2.h"
#include "Tasks/Kernel.h"

TestApplication::TestApplication(void) {}

TestApplication::~TestApplication(void) {}

void TestApplication::init() {
	defaultInit();

	std::shared_ptr<Task> task = std::make_shared<TestTask2>();

	Kernel::getInstance()->addTask(task);
}