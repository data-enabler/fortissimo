#pragma once
#include "MMObject.h"

class Functor : public MMObject
{
public:
	virtual void operator () () = 0;
};