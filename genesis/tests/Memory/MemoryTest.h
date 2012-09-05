#pragma once
#include "Test.h"

class MemoryTest : public Test
{
public:
	static int numDeleted;
	MemoryTest(void);
	~MemoryTest(void);
	bool run();
};