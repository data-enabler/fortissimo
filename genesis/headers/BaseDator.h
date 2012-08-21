#pragma once
#include <string>
#include "MMObject.h"

class BaseDator : public MMObject
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