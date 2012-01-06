#include "MMObject.h"
using namespace std;

set<MMObject*> MMObject::liveObjects;
set<MMObject*> MMObject::deadObjects;

MMObject::MMObject(void)
{
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
		MMObject *o = (*it);

		if (logWarnings) {
			// log an error message
		}
		
		delete o;
	}
}