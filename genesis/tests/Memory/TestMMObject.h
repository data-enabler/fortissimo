#pragma once
#include "Memory/MMObject.h"
#include "Memory/MemoryTest.h"

class TestMMObject : public MMObject
{
protected:
	char c;
	char arr[8192];

public:
	TestMMObject() : c('a') {}

	TestMMObject(char name) : c(name) {}

	~TestMMObject()
	{
		MemoryTest::numDeleted++;
	}

	AUTO_SIZE
};