#pragma once
#include "BaseDator.h"
#include "StringConvert.h"

template<class T>
class ListDator : public BaseDator
{
protected:
	std::list<T>& values;

public:
	ListDator(std::list<T>& v) : values(v) {}

	BaseDator& operator =(std::string& s)
	{values.clear(); values.push_back(StringConvert<T>::toVal(s)); return *this;}
	
	BaseDator& operator +=(std::string& s)
	{values.push_back(StringConvert<T>::toVal(s)); return *this;}
	
	BaseDator& operator -=(std::string& s)
	{values.remove(StringConvert<T>::toVal(s)); return *this;}
	
	bool operator ==(std::string& s)
	{return (std::find(values.begin(), values.end(), StringConvert<T>::toVal(s)) != values.end());}
	
	bool operator !=(std::string& s) {return !(s == (*this));}

	bool hasMultipleValues() {return true;}

	//operator std::string() {return StringConvert<T>::toString(values.back());}
	operator std::string()
	{
		std::stringstream str;
		str.unsetf(std::ios::skipws);
		for (std::list<T>::iterator it = values.begin(); it != values.end(); it++)
			str << *it;
		std::string res;
		str >> res;
		return res;
	}
	operator std::list<T>&() {return values;}

	AUTO_SIZE;
};