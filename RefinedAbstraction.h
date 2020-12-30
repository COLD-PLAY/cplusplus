

#ifndef DESIGNPATTERN_REFINED_H
#define DESIGNPATTERN_REFINED_H

#include "Abstraction.h"

#include <iostream>

using namespace std;

class PullChainSwitch : public ISwitch
{
public:
	PullChainSwitch(IElectricalEquipment* ee) : ISwitch(ee) {}
	
	virtual void On() override
	{
		cout << "Turn on the equipment with a zipper switch." << endl;
		m_pEe->PowerOn();
	}

	virtual void Off() override
	{
		cout << "Turn off the equipment with a zipper switch." << endl;
		m_pEe->PowerOff();
	}
};

class TwoPositionSwitch : public ISwitch
{
public:
	TwoPositionSwitch(IElectricalEquipment* ee) : ISwitch(ee) {}
	
	virtual void On() override
	{
		cout << "Turn on the equipment with a two-position switch." << endl;
		m_pEe->PowerOn();
	}

	virtual void Off() override
	{
		cout << "Turn off the equipment with a two-position switch." << endl;
		m_pEe->PowerOff();
	}
};

#endif