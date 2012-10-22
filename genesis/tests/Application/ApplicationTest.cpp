#include "ApplicationTest.h"
#include <iostream>
#include "TestApplication.h"

bool ApplicationTest::failFlag;

ApplicationTest::ApplicationTest(void) {failFlag = false;}

ApplicationTest::~ApplicationTest(void) {}

bool ApplicationTest::run() {
	std::cout << "Running Application Test..." << std::endl;
	TestApplication app;
	app.init();
	app.run();
	if (!failFlag) std::cout << "All tests passed." << std::endl;
	else std::cout << "Test failed." << std::endl;
	return failFlag;
}