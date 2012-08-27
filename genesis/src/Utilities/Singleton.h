#pragma once
#include <cassert>

template<class T>
class Singleton
{
private:
	static T* singleton;
	T& operator =(T const&) {};

protected:
	Singleton()
	{
		assert(!singleton);
		// use a cunning trick to get the singleton pointing to the start of
        // the whole, rather than the start of the Singleton part of the object
		int offset = (int)(T*)1 - (int)(Singleton<T>*)(T*)1;
		singleton = (T*)((int) this + offset);
	}

	~Singleton()
	{
		assert(singleton);
		singleton = 0;
	}

public:
	static T* getInstance()
	{
		if (!singleton) new T();
		return singleton;
	}
};

template <class T> T* Singleton<T>::singleton = 0;