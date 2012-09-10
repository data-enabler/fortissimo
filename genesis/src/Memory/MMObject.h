#pragma once
#include <functional>
#include <memory>
#include <unordered_map>
#include <stack>
#include <typeindex>
#include <utility>

#define _VARIADIC_MAX 5

class MMObject : public std::enable_shared_from_this<MMObject>
{
protected:
	struct Recycle
	{
		template<class T> inline void operator()(T* ptr)
		{
			ptr->~T();
			deadObjects[typeid(ptr)].push(ptr);
		}

	};

private:
	static std::unordered_map<std::type_index, long> createCount;
	static std::unordered_map<std::type_index, std::stack<void*>> deadObjects;
	static Recycle recycler;

protected:
	MMObject(void) {}

public:
	virtual ~MMObject(void) {}

	template<class T> static inline std::shared_ptr<T> create()
	{
		T* ptr;
		std::stack<void*>& corpses = deadObjects[typeid(ptr)];
		if (corpses.empty()) {
			ptr = new T();
		} else {
			ptr = new (corpses.top()) T();
			corpses.pop();
		}
		return std::shared_ptr<T>(ptr, recycler);
	}

#ifdef _MSC_VER
#	if _MSC_VER == 1800
#		define _MMOBJECT_CREATE(TEMPLATE_LIST, PADDING_LIST, LIST, COMMA, X1, X2, X3, X4) \
template<class T COMMA LIST(_CLASS_TYPE)> static inline std::shared_ptr<T> create(LIST(_TYPE_REFREF_ARG)) \
{ \
	T* ptr; \
	if (deadObjects[typeid(ptr)].empty()) { \
		ptr = new T(LIST(_FORWARD_ARG)); \
	} else { \
	} \
	return std::shared_ptr<T>(ptr); \
}
_VARIADIC_EXPAND_0X(_MMOBJECT_CREATE, , , , )
#		undef _MMOBJECT_CREATE
#	endif
#elif __GXX_EXPERIMENTAL_CXX0X__
template<class T> static inline std::shared_ptr<T> create()
{
	std::shared_ptr<MMObject> obj = std::make_shared<T>();
	return obj;
}

template<class T, class Arg1, class... Args> static inline std::shared_ptr<T> create(Arg1&& arg1, Args&&... args)
{
	std::shared_ptr<MMObject> obj = std::make_shared<T>(std::forward<Arg1>(arg1), std::forward<Args>(args)...);
	return obj;
}
#endif

	static void trim() {};

	virtual unsigned long size()=0;
};

#define AUTO_SIZE unsigned long size(){return sizeof(*this);}