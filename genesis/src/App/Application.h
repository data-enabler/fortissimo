#pragma once

class Application
{
protected:
	void defaultInit(void);
public:
	Application(void);
	virtual ~Application(void);
	virtual void init(void) = 0;
	void run(void);
};