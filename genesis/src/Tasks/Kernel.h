#pragma once
#include "Utilities/Singleton.h"
#include <map>
#include <set>
#include "Task.h"
#include "Memory/MMPointer.h"

class Kernel : public Singleton<Kernel>
{
protected:
	// internally, maps keep their elements ordered from least to greatest, which is convenient
	std::multimap<int, MMPointer<Task>> taskList;
	std::set<MMPointer<Task>> pausedTaskList;

public:
	Kernel(void);
	virtual ~Kernel(void);

	int execute();

	bool addTask(MMPointer<Task>& t);
	void suspendTask(MMPointer<Task>& t);
	void resumeTask(MMPointer<Task>& t);
	void removeTask(MMPointer<Task>& t);
	void killAllTasks();
};

