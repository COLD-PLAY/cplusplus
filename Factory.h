
#ifndef DESIGNPATTERN_FACTORY_H
#define DESIGNPATTERN_FACTORY_H

#include "Product.h"

class Factory
{
public:
	enum FACTORY_TYPE
	{
		BENZ_FACTORY,
		BMW_FACTORY,
		AUDI_FACTORY
	};

	virtual ICar* CreateCar() = 0;
	virtual IBike* CreateBike() = 0;
	static Factory* CreateFactory(FACTORY_TYPE factory);
};
#endif