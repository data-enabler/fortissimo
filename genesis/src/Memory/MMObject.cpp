#include "MMObject.h"
#include "Logging/Log.h"

using namespace std;

set<MMObject*> MMObject::liveObjects;
set<MMObject*> MMObject::deadObjects;

MMObject::MMObject(void)
{
	refcount = 0;
	liveObjects.insert(this);
}

MMObject::~MMObject(void)
{
}

void MMObject::addRef()
{
	refcount++;
}

void MMObject::release()
{
	refcount--;
	if (refcount <= 0) {
		liveObjects.erase(this);
		deadObjects.insert(this);
	}
}

void MMObject::collectGarbage()
{
	for (set<MMObject*>::iterator it = deadObjects.begin(); it != deadObjects.end(); it++) {
		delete (*it);
	}

	deadObjects.clear();
}

void MMObject::collectRemainingObjects(bool logWarnings=false)
{
	collectGarbage();
	for (set<MMObject*>::iterator it = liveObjects.begin(); it != liveObjects.end(); it++) {
		MMObject* o = *it;

		if (logWarnings) {
			Log::get().write(Log::LOG_APP, "Error: Unreleased Memory of type %s and size %i", typeid(*o).name(), sizeof(*o));
		}
		
		delete o;
	}
}