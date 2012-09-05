#include "MMObject.h"
#include "Logging/Log.h"

std::list<std::shared_ptr<MMObject>> MMObject::liveObjects;

MMObject::MMObject(void)
{
}

MMObject::~MMObject(void)
{
}

void MMObject::collectGarbage()
{
	for (std::list<std::shared_ptr<MMObject>>::iterator it = liveObjects.begin(); it != liveObjects.end();) {
		if (it->use_count() <= 1) {
			it->reset();
			liveObjects.erase(it++);
		} else {
			++it;
		}
	}
}

void MMObject::collectRemainingObjects(bool logWarnings=false)
{
	collectGarbage();
	for (std::list<std::shared_ptr<MMObject>>::iterator it = liveObjects.begin(); it != liveObjects.end(); it++) {
		if (logWarnings) {
			Log::get().write(Log::LOG_APP, "Error: Unreleased Memory of type %s and size %i", typeid(**it).name(), (*it)->size());
		}
		it->reset();
	}
}