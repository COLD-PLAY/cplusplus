
#ifndef DESIGNPATTERN_CONCRETE_PRODUCT_H
#define DESIGNPATTERN_CONCRETE_PRODUCT_H

#include "Product.h"

class BenzCar : public ICar
{
public:
	string Name()
	{
		return "BenzCar";
	}
};

class BenzBike : public IBike
{
public:
	string Name()
	{
		return "BenzBike";
	}
};

class BmwCar : public ICar
{
public:
	string Name()
	{
		return "BmwCar";
	}
};

class BmwBike : public IBike
{
public:
	string Name()
	{
		return "BmwBike";
	}
};

class AudiCar : public ICar
{
public:
	string Name()
	{
		return "AudiCar";
	}
};

class AudiBike : public IBike
{
public:
	string Name()
	{
		return "AudiBike";
	}
};

#endif