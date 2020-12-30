
#ifndef DESIGNPATTER_ABSTRACTION_H
#define DESIGNPATTER_ABSTRACTION_H

#include "Implementor.h"

class ISwitch
{
public:
	ISwitch(IElectricalEquipment* ee) { m_pEe = ee; }
	virtual ~ISwitch() {}
	virtual void On() = 0;
	virtual void Off() = 0;

protected:
	IElectricalEquipment* m_pEe;
};

#endif