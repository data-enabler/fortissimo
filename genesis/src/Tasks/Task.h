#include "Memory\MMObject.h"

class Task : public MMObject
{
public:
	bool canKill;
	int priority;
	
	Task() {canKill = false; priority = 500;}

	virtual bool start() = 0;
	virtual void onSuspend() {};
	virtual void update() = 0;
	virtual void onResume() {};
	virtual void stop() = 0;
};