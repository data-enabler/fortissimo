#pragma once
#include <set>
using namespace std;

class MMObject
{
private:
	static set<MMObject*> liveObjects;
	static set<MMObject*> deadObjects;
	long refcount;
protected:
	MMObject(void);
	virtual ~MMObject(void);
public:
	void addRef();
	void release();
	static void collectGarbage();
	static void collectRemainingObjects(bool logWarnings);
	virtual unsigned long size()=0;
};

#define AUTO_SIZE unsigned long size(){return sizeof(*this);}