#include "MemoryTest.h"
#include <cassert>
#include <iostream>
#include "Timing/ProfileSample.h"
#include "TestMMObject.h"

int MemoryTest::numDeleted;

MemoryTest::MemoryTest(void)
{
}

MemoryTest::~MemoryTest(void)
{
}

bool MemoryTest::run()
{
	std::cout << "Running Memory Test..." << std::endl;
	numDeleted = 0;

	std::shared_ptr<MMObject> a1 = MMObject::create<TestMMObject>();
	std::shared_ptr<MMObject> a2 = a1;
	std::shared_ptr<MMObject> a3 = a1;

	std::shared_ptr<MMObject> b1 = MMObject::create<TestMMObject>('b');
	std::shared_ptr<MMObject> b2 = b1;

	std::shared_ptr<MMObject> c1 = MMObject::create<TestMMObject>('c');

	MMObject::collectGarbage();
	assert(numDeleted == 0);

	a3.reset();
	b2.reset();
	c1.reset();
	MMObject::collectGarbage();
	assert(numDeleted == 1);

	a2.reset();
	b1.reset();
	MMObject::collectGarbage();
	assert(numDeleted == 2);

	MMObject::collectRemainingObjects(false);
	assert(numDeleted == 2);

	//Test Performance
	{
		ProfileSample p("Memory Test");
		{
			ProfileSample p1("Without Garbage Collection");
			for(int i = 0; i < 10000; i++) {
				{
					std::shared_ptr<TestMMObject> ptr = std::make_shared<TestMMObject>();
				}
			}
		}

		{
			ProfileSample p2("With Garbage Collection");
			for(int i = 0; i < 10000; i++) {
				{
					std::shared_ptr<TestMMObject> ptr = MMObject::create<TestMMObject>();
				}
			}
		} 
		MMObject::collectGarbage();
	}


	ProfileSample::output();

	std::cout << "All tests passed." << std::endl;

	return true;
}