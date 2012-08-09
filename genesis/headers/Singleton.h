#pragma once
template<class T>

class Singleton
{
private:
	static T* ms_singleton;
	
public:
	Singleton()
	{
		assert(!ms_singleton);
		// use a cunning trick to get the singleton pointing to the start of
        // the whole, rather than the start of the Singleton part of the object
		int offset = (int)(T*)1 - (int)(Singleton<T>*)(T*)1;
		ms_singleton = (T*)((int) this + offset);
	}

	~Singleton()
	{
		assert(ms_singleton);
		ms_singleton = 0;
	}

	static T& getSingleton()
	{
		assert(ms_singleton);
		return *ms_singleton;
	}

	static T* getSingletonPtr()
	{
		assert(ms_singleton);
		return ms_singleton;
	}
};

template <class T> T* Singleton<T>::ms_singleton = 0;