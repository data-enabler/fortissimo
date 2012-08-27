#pragma once
#include "MMObject.h"
template<class T>

class MMWrapper : public MMObject
{
protected:
	T* obj;
public:
	// basic constructor
	MMWrapper(void)
	{
		obj = 0;
	}

	// constructor from pointer
	MMWrapper(T* o)
	{
		obj = 0;
		*this = o;
	}

	// copy constructor
	MMWrapper(const MMWrapper<T>& p)
	{
		obj = 0;
		*this = p;
	}

	// destructor
	~MMWrapper(void) {}

	// assignment operator - pointer
	inline void operator =(T* o)
	{
		obj = o;
	}

	// assignment operator - wrapper
	inline void operator =(const MMWrapper<T>& p)
	{
		obj = p.obj;
	}

	// access as reference
	inline T& operator *() const
	{
		assert(obj != 0 && "Tried to * on a NULL wrapper");
		return *obj;
	}

	// access as pointer
	inline T* operator ->() const
	{
		assert(obj != 0 && "Tried to -> on a NULL wrapper");
		return obj;
	}

	// convert to type T*
	inline operator T*() const
	{
		return obj;
	}

	// null pointer check
	inline bool isValid() const
	{
		return (obj != 0);
	}

	// negation
	inline bool operator !() const
	{
		return !(obj);
	}

	// equivalence
	inline bool operator ==(const MMWrapper<T> &p) const
	{
		return (obj == p.obj);
	}

	inline bool operator ==(const T* o) const
	{
		return (obj == o);
	}

	AUTO_SIZE
};