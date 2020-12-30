
#ifndef DESIGNPATTERN_CONCRETE_IMPLEMENTOR_H
#define DESIGNPATTERN_CONCRETE_IMPLEMENTOR_H

#include "Implementor.h"
#include <iostream>

using namespace std;

class Light : public IElectricalEquipment
{
public:
	virtual void PowerOn() override
	{
		cout << "Light is on." << endl;
	}
	virtual void PowerOff() override
	{
		cout << "Light is off." << endl;
	}
};

class Fan : public IElectricalEquipment
{
public:
	virtual void PowerOn() override
	{
		cout << "Fan is on." << endl;
	}
	virtual void PowerOff() override
	{
		cout << "Fan is off." << endl;
	}
};

#endif