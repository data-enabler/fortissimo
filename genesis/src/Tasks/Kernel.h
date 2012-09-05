#pragma once
#include "Utilities/Singleton.h"
#include <map>
#include <set>
#include "Task.h"

class Kernel : public Singleton<Kernel>
{
protected:
	// internally, maps keep their elements ordered from least to greatest, which is convenient
	std::multimap<int, std::shared_ptr<Task>> taskList;
	std::set<std::shared_ptr<Task>> pausedTaskList;

public:
	Kernel(void);
	virtual ~Kernel(void);

	int execute();

	bool addTask(std::shared_ptr<Task>& t);
	void suspendTask(std::shared_ptr<Task>& t);
	void resumeTask(std::shared_ptr<Task>& t);
	void removeTask(std::shared_ptr<Task>& t);
	void killAllTasks();
};