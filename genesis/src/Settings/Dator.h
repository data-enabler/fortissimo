#pragma once
#include "BaseDator.h"
#include "Tools/StringManip.h"

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

template<> BaseDator& Dator<std::string>::operator +=(std::string& s) {target.append(StringConvert<std::string>::toVal(s)); return *this;}
template<> BaseDator& Dator<std::string>::operator -=(std::string& s) {return *this;}

template<> BaseDator& Dator<bool>::operator +=(std::string& s) {target =  StringConvert<bool>::toVal(s); return *this;}
template<> BaseDator& Dator<bool>::operator -=(std::string& s) {target = !StringConvert<bool>::toVal(s); return *this;}

// fuck this shit
//template<class T> 
//class Dator<std::list<T>>
//{
//protected:
//	std::list<T>& target;

//public:
//	Dator(std::list<T>& l) : target(l) {}
//	
//	BaseDator& operator =(std::string& s)
//		{target.clear(); target.push_back(StringConvert<T>::toVal(s)); return *this;}

//	BaseDator& operator +=(std::string& s)
//		{target.push_back(StringConvert<T>::toVal(s)); return *this;}
//	
//	BaseDator& operator -=(std::string& s)
//		{target.remove(StringConvert<T>::toVal(s)); return *this;}
//	
//	bool operator ==(std::string& s)
//		{return (std::find(target.begin(), target.end(), StringConvert<T>::toVal(s)) != target.end());}
//	
//	bool operator !=(std::string& s) {return !((*this) == s);}

//	bool hasMultipleValues() {return true;}

//	//operator std::string() {return StringConvert<T>::toString(target.back());}
//	operator std::string()
//	{
//		std::stringstream str;
//		str.unsetf(std::ios::skipws);
//		for (std::list<T>::iterator it = target.begin(); it != target.end(); it++)
//			str << *it << ';';
//		std::string res;
//		str >> res;
//		return res;
//	}

//	operator std::list<T>&() {return target;}

//	AUTO_SIZE;
//};