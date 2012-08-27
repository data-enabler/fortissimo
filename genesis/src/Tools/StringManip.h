#pragma once
#include <algorithm>
#include <cctype>
#include <list>
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

class StringManip
{
public:
	static std::list<std::string> split(std::string str, std::list<std::string>& out, char delim)
	{
		std::stringstream ss(str);
		std::string piece;
		while (std::getline(ss, piece, delim)) {
			out.push_back(piece);
		}
		return out;
	}

	static void removeWhitespace(std::string& str)
	{
		std::string::iterator newEnd = std::remove_if(str.begin(), str.end(), ::isspace);
		str.erase(newEnd, str.end());
	}

	static void removeWhitespace(std::string& str, int begin, int end)
	{
		std::string::iterator start = str.begin() + begin;
		std::string::iterator stop  = str.begin() + end;
		
		while (start != stop) {
			if (::isspace(*start)) {
				str.erase(start);
				stop--;
			} else {
				start++;
			}
		}
	}
};