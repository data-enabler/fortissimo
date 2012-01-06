#pragma once
template<class T>

class MMPointer
{
protected:
	T* obj;
public:
	// basic constructor
	MMPointer(void)
	{
		obj = 0;
	}

	// constructor from pointer
	MMPointer(T* o)
	{
		obj = 0;
		*this = o;
	}

	// copy constructor
	MMPointer(const MMpointer<T> &p)
	{
		obj = 0;
		*this = p;
	}

	// destructor
	~MMPointer(void)
	{
		if (obj) obj->release();
	}

	// assignment operator - normal pointer
	inline operator =(T* o)
	{
		if (obj) obj->release();
		obj = o;
		if (obj) obj->addRef();
	}

	// assignment operator - memory managed pointer
	inline operator =(const MMPointer<T> &p)
	{
		if (obj) obj->release();
		obj = p.obj;
		if (obj) obj->addRef();
	}

	// access as reference
	inline T& operator *() const
	{
		assert(obj != 0 && "Tried to * on a NULL smart pointer");
		return *obj;
	}

	// access as pointer
	inline T* operator ->() const
	{
		assert(obj != 0 && "Tried to -> on a NULL smart pointer");
		return obj;
	}

	// convert to type T*
	inline operator T*() const
	{
		return obj
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
	inline bool operator ==(const MMPointer<T> &p) const;
	{
		return (obj == p.obj);
	}

	inline bool operator ==(const T* o) const
	{
		return (obj == o);
	}
};

