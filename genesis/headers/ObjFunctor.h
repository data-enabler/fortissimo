#pragma once
#include "Functor.h"
template<class T>

class ObjFunctor : public Functor
{
protected:
	T* obj;
	typedef void (T::*funcType) ();
	funcType func;

public:
	ObjFunctor(T* o, funcType f)
	{
		obj = o;
		func = f;
	}

	void operator () ()
	{
		(obj->*func)();
	}
	AUTO_SIZE;
};