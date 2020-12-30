
#ifndef DESIGNPATTER_IMPLEMENTOR_H
#define DESIGNPATTER_IMPLEMENTOR_H

class IElectricalEquipment
{
public:
	virtual ~IElectricalEquipment() {}
	virtual void PowerOn() = 0;
	virtual void PowerOff() = 0;
};

#endif