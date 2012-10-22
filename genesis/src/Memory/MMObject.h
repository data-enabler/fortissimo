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

#ifdef _MSC_VER
#	if _MSC_VER == 1700
#		define _MMOBJECT_CREATE(TEMPLATE_LIST, PADDING_LIST, LIST, COMMA, X1, X2, X3, X4) \
template<class T COMMA LIST(_CLASS_TYPE)> static inline std::shared_ptr<T> create(LIST(_TYPE_REFREF_ARG)) \
{ \
	std::stack<void*>& corpses = deadObjects[typeid(T*)]; \
	if (corpses.empty()) { \
		return std::shared_ptr<T>(new T(LIST(_FORWARD_ARG)), recycler); \
	} else { \
		void* space = corpses.top(); \
		corpses.pop(); \
		return std::shared_ptr<T>(new (space) T(LIST(_FORWARD_ARG)), recycler); \
	} \
}
_VARIADIC_EXPAND_0X(_MMOBJECT_CREATE, , , , )
#		undef _MMOBJECT_CREATE
#	endif
#elif __GXX_EXPERIMENTAL_CXX0X__
template<class T> static inline std::shared_ptr<T> create()
{
	std::stack<void*>& corpses = deadObjects[typeid(T*)];
	if (corpses.empty()) {
		return std::shared_ptr<T>(new T(), recycler);
	} else {
		void* space = corpses.top();
		corpses.pop();
		return std::shared_ptr<T>(new (space) T(), recycler);
	}
}

template<class T, class Arg1, class... Args> static inline std::shared_ptr<T> create(Arg1&& arg1, Args&&... args)
{
	std::stack<void*>& corpses = deadObjects[typeid(T*)];
	if (corpses.empty()) {
		return std::shared_ptr<T>(new T(std::forward<Arg1>(arg1), std::forward<Args>(args)...), recycler);
	} else {
		void* space = corpses.top();
		corpses.pop();
		return std::shared_ptr<T>(new (space) T(std::forward<Arg1>(arg1), std::forward<Args>(args)...), recycler);
	}
}
#endif

	static void trim() {};
	
	static void clear() {
		for (std::unordered_map<std::type_index, std::stack<void*>>::iterator it = deadObjects.begin();
																			  it != deadObjects.end(); ++it) {
			while (!it->second.empty()) {
				delete it->second.top();
				it->second.pop();
			}
		}
		deadObjects.clear();
	}

	virtual unsigned long size() {return sizeof(*this);}
};