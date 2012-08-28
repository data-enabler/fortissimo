#include "Kernel.h"
#include <allegro5/allegro.h>
#include "Timing/ProfileSample.h"
#include "constants.h"

Kernel::Kernel(void)
{
	al_init();
}

Kernel::~Kernel(void)
{
	al_uninstall_system();
}

int Kernel::execute()
{
	while (taskList.size()) {
		{
			ProfileSample ps("Kernel Task Loop");

			// update tasks
			std::multimap<int, MMPointer<Task>>::reverse_iterator rit;
			for (rit = taskList.rbegin(); rit != taskList.rend();) {
				Task* t = rit->second;
				rit++;
				if (!t->canKill) t->update();
			}

			// remove dead tasks
			std::multimap<int, MMPointer<Task>>::iterator it;
			for (it = taskList.begin(); it != taskList.end();) {
				Task* t = it->second;
				if (t->canKill) {
					t->stop();
					taskList.erase(it++);
					t = 0;
				}
			}

			MMObject::collectGarbage();
		}
#ifdef DEBUG
		ProfileSample::output();
#endif
	}

	return 0;
}

bool Kernel::addTask(MMPointer<Task>& t)
{
	if (!t->start()) return false;
	taskList.insert(std::pair<int, MMPointer<Task>>(t->priority, t));
	return true;
}

void Kernel::suspendTask(MMPointer<Task>& t)
{
	std::multimap<int, MMPointer<Task>>::iterator it;
	std::pair<std::multimap<int, MMPointer<Task>>::iterator
			, std::multimap<int, MMPointer<Task>>::iterator> range;
	range = taskList.equal_range(t->priority);

	for (it = range.first; it != range.second; it++) {
		if (it->second == t) {
			t->onSuspend();
			taskList.erase(it);
			pausedTaskList.insert(t);
			break;
		}
	}
}

void Kernel::resumeTask(MMPointer<Task>& t)
{
	if (pausedTaskList.find(t) != pausedTaskList.end()) {
		t->onResume();
		pausedTaskList.erase(t);
		taskList.insert(std::pair<int, MMPointer<Task>>(t->priority, t));
	}
}

void Kernel::removeTask(MMPointer<Task>& t)
{
	std::multimap<int, MMPointer<Task>>::iterator it;
	std::pair<std::multimap<int, MMPointer<Task>>::iterator
			, std::multimap<int, MMPointer<Task>>::iterator> range;
	range = taskList.equal_range(t->priority);

	for (it = range.first; it != range.second; it++) {
		if (it->second == t) {
			t->canKill = true;
			break;
		}
	}
}