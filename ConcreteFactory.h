
#ifndef DESIGNPATTERN_CONCRETE_FACTORY_H
#define DESIGNPATTERN_CONCRETE_FACTORY_H

#include "Factory.h"
#include "ConcreteProduct.h"

class BenzFactory : public Factory
{
public:
	ICar* CreateCar()
	{
		return new BenzCar();
	}
	IBike* CreateBike()
	{
		return new BenzBike();
	}
};

class BmwFactory : public Factory
{
public:
	ICar* CreateCar()
	{
		return new BmwCar();
	}
	IBike* CreateBike()
	{
		return new BmwBike();
	}
};

class AudiFactory : public Factory
{
public:
	ICar* CreateCar()
	{
		return new AudiCar();
	}
	IBike* CreateBike()
	{
		return new AudiBike();
	}
};

#endif