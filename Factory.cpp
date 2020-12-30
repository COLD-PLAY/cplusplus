
#include "Factory.h"
#include "ConcreteFactory.h"

Factory* Factory::CreateFactory(FACTORY_TYPE factory)
{
	Factory* pFactory = nullptr;
	switch (factory)
	{
	case BENZ_FACTORY:
		pFactory = new BenzFactory();
		break;
	case BMW_FACTORY:
		pFactory = new BmwFactory();
		break;
	case AUDI_FACTORY:
		pFactory = new AudiFactory();
		break;
	default:
		break;
	}
	return pFactory;
}