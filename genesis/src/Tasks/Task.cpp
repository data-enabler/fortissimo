#include "Task.h"
#include <limits>

short Task::getPriority() {return priority;}

void Task::setPriority(short p) {priority = p;}

void Task::setPriority(Task& relativeTo, short p) {
	long sum = relativeTo.getPriority() + p;
	if (sum > std::numeric_limits<short>::max()) {
		priority = std::numeric_limits<short>::max();
	} else if (sum < std::numeric_limits<short>::min()) {
		priority = std::numeric_limits<short>::min();
	} else {
		priority = sum;
	}
	return;
}