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
			std::multimap<short, std::shared_ptr<Task>>::reverse_iterator rit;
			for (rit = taskList.rbegin(); rit != taskList.rend();) {
				std::shared_ptr<Task> t = rit->second;
				rit++;
				if (!t->canKill) t->update();
			}

			// remove dead tasks
			std::multimap<short, std::shared_ptr<Task>>::iterator it;
			for (it = taskList.begin(); it != taskList.end();) {
				std::shared_ptr<Task> t = it->second;
				if (t->canKill) {
					t->stop();
					t.reset();
					taskList.erase(it++);
				} else ++it;
			}

			// trim memory pool
			//MMObject::trim();
		}
#ifdef DEBUG
		ProfileSample::output();
#endif
	}

	return 0;
}

bool Kernel::addTask(std::shared_ptr<Task>& t)
{
	if (!t->start()) return false;
	taskList.insert(std::pair<short, std::shared_ptr<Task>>(t->getPriority(), t));
	return true;
}

void Kernel::suspendTask(std::shared_ptr<Task>& t)
{
	std::multimap<short, std::shared_ptr<Task>>::iterator it;
	std::pair<std::multimap<short, std::shared_ptr<Task>>::iterator
			, std::multimap<short, std::shared_ptr<Task>>::iterator> range;
	range = taskList.equal_range(t->getPriority());

	for (it = range.first; it != range.second; it++) {
		if (it->second == t) {
			t->onSuspend();
			taskList.erase(it);
			pausedTaskList.insert(t);
			break;
		}
	}
}

void Kernel::resumeTask(std::shared_ptr<Task>& t)
{
	if (pausedTaskList.find(t) != pausedTaskList.end()) {
		t->onResume();
		pausedTaskList.erase(t);
		taskList.insert(std::pair<int, std::shared_ptr<Task>>(t->getPriority(), t));
	}
}

void Kernel::removeTask(std::shared_ptr<Task>& t)
{
	std::multimap<short, std::shared_ptr<Task>>::iterator it;
	std::pair<std::multimap<short, std::shared_ptr<Task>>::iterator
			, std::multimap<short, std::shared_ptr<Task>>::iterator> range;
	range = taskList.equal_range(t->getPriority());

	for (it = range.first; it != range.second; it++) {
		if (it->second == t) {
			t->canKill = true;
			break;
		}
	}
}