#pragma once
#include <memory>
#include <list>
#include <utility>

#define _VARIADIC_MAX 5

class MMObject : public std::enable_shared_from_this<MMObject>
{
private:
	static std::list<std::shared_ptr<MMObject>> liveObjects;

protected:
	MMObject(void);

public:
	virtual ~MMObject(void);

#ifdef _MSC_VER
#	if _MSC_VER == 1700
#		define _MMOBJECT_CREATE(TEMPLATE_LIST, PADDING_LIST, LIST, COMMA, X1, X2, X3, X4) \
template<class T COMMA LIST(_CLASS_TYPE)> static inline std::shared_ptr<T> create(LIST(_TYPE_REFREF_ARG)) \
{ \
	std::shared_ptr<T> ptr = std::make_shared<T>(LIST(_FORWARD_ARG)); \
	liveObjects.push_back(ptr); \
	return ptr; \
}
_VARIADIC_EXPAND_0X(_MMOBJECT_CREATE, , , , )
#		undef _MMOBJECT_CREATE
#	endif
#elif __GXX_EXPERIMENTAL_CXX0X__
template<class T> static inline std::shared_ptr<T> create()
{
	std::shared_ptr<MMObject> obj = std::make_shared<T>();
	liveObjects.push_back(obj);
	return obj->shared_from_this();
}

template<class T, class Arg1, class... Args> static inline std::shared_ptr<T> create(Arg1&& arg1, Args&&... args)
{
	std::shared_ptr<MMObject> obj = std::make_shared<T>(std::forward<Arg1>(arg1), std::forward<Args>(args)...);
	liveObjects.push_back(obj);
	return obj->shared_from_this();
}
#endif

	static void collectGarbage();
	static void collectRemainingObjects(bool logWarnings);

	virtual unsigned long size()=0;
};

#define AUTO_SIZE unsigned long size(){return sizeof(*this);}