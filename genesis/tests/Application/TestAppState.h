#pragma once
#include "App/AppState.h"
#include <memory>

class TestAppState : public AppState
{
private:
	std::shared_ptr<Task> t1;
	std::shared_ptr<Task> t2;
	std::shared_ptr<Task> t3;
	std::shared_ptr<Task> t4;

public:
	TestAppState(void);
	~TestAppState(void);
	bool start();
	void update();
	void stop();
};