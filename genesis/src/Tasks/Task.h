#pragma once

class Task
{
protected:
	short priority;

public:
	bool canKill;
	
	Task(void) {canKill = false; priority = 0;}
	virtual ~Task(void) {}

	virtual bool start() = 0;
	virtual void onSuspend() {};
	virtual void update() = 0;
	virtual void onResume() {};
	virtual void stop() = 0;

	short getPriority();
	void setPriority(short p);
	void setPriority(Task& relativeTo, short p);
};