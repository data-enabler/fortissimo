#pragma once
#include "BaseDator.h"
#include "StringConvert.h"

template<class T>
class Dator : public BaseDator
{
protected:
	T& target;

public:
	Dator(T& t) : target(t) {}

	BaseDator& operator =(std::string& s)  {target  = StringConvert<T>::toVal(s); return *this;}
	BaseDator& operator +=(std::string& s) {target += StringConvert<T>::toVal(s); return *this;}
	BaseDator& operator -=(std::string& s) {target -= StringConvert<T>::toVal(s); return *this;}
	bool operator ==(std::string& s) {return s == (std::string) (*this);}
	bool operator !=(std::string& s) {return (s == (std::string) (*this));}

	bool hasMultipleValues() {return false;}

	operator std::string() {return StringConvert<T>::toString(target);}

	AUTO_SIZE;
};