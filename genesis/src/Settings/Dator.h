#pragma once
#include <string>
#include "Tools/StringManip.h"

class BaseDator 
{
protected:
	BaseDator() {}
	BaseDator(BaseDator& b) {(*this)=b;}
public:
	virtual BaseDator& operator =(std::string& s) = 0;
	virtual BaseDator& operator +=(std::string& s) = 0;
	virtual BaseDator& operator -=(std::string& s) = 0;
	virtual bool operator ==(std::string& s) = 0;
	virtual bool operator !=(std::string& s) = 0;

	virtual bool hasMultipleValues() = 0;

	virtual operator std::string() = 0;
};

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
};

template<> BaseDator& Dator<std::string>::operator +=(std::string& s) {target.append(StringConvert<std::string>::toVal(s)); return *this;}
template<> BaseDator& Dator<std::string>::operator -=(std::string& s) {return *this;}

template<> BaseDator& Dator<bool>::operator +=(std::string& s) {target =  StringConvert<bool>::toVal(s); return *this;}
template<> BaseDator& Dator<bool>::operator -=(std::string& s) {target = !StringConvert<bool>::toVal(s); return *this;}

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
	
	bool operator !=(std::string& s) {return !((*this) == s);}

	bool hasMultipleValues() {return true;}

	//operator std::string() {return StringConvert<T>::toString(values.back());}
	operator std::string()
	{
		std::stringstream str;
		str.unsetf(std::ios::skipws);
		for (std::list<T>::iterator it = values.begin(); it != values.end(); it++)
			str << *it << ';';
		std::string res;
		str >> res;
		return res;
	}
	operator std::list<T>&() {return values;}
};