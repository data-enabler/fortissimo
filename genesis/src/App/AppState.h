#pragma once
#include "Tasks/Task.h"

class AppState : public Task
{
protected:
	void defaultInit();
	void addSystemTasks(bool priorityRelativeToState = true);
public:
	AppState(void);
	virtual ~AppState(void);
};