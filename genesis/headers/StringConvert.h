#pragma once
#include <string>
#include <sstream>

template<class T>
class StringConvert
{
public:
	static T toVal(std::string& s)
	{
		std::stringstream str;
		str.unsetf(std::ios::skipws);
		str << s;
		T res;
		str >> res;
		return res;
	}

	static std::string toString(T& val)
	{
		std::stringstream str;
		str.unsetf(std::ios::skipws);
		str << val;
		std::string res;
		str >> res;
		return res;
	}
};