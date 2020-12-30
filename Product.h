
#ifndef DESIGNPATTERN_PRODUCT_H
#define DESIGNPATTERN_PRODUCT_H

#include <string>
using std::string;

class ICar
{
public:
	virtual string Name() = 0;
};

class IBike
{
public:
	virtual string Name() = 0;
};

#endif