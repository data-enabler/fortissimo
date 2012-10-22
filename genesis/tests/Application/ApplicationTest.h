#pragma once
#include "Test.h"

class ApplicationTest : public Test
{
public:
	static bool failFlag;
	ApplicationTest(void);
	~ApplicationTest(void);
	bool run();
};