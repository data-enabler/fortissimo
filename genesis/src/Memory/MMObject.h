#pragma once
#include <set>

class MMObject
{
private:
	static std::set<MMObject*> liveObjects;
	static std::set<MMObject*> deadObjects;
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