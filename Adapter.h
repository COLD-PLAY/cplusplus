
#ifndef DESIGNPATTERN_ADAPTER_H
#define DESIGNPATTERN_ADAPTER_H

#include "Adaptee.h"
#include "Target.h"

#ifndef SAFE_DELETE
#define SAFE_DELETE(p) { if (p) { delete(p); (p) = nullptr; } }

#endif

class PowerAdapter : public IRussiaSockt
{
public:
	PowerAdapter() : m_pCharger(new OwnCharger()) {}
	~PowerAdapter()
	{
		SAFE_DELETE(m_pCharger);
	}
	void Charge()
	{
		m_pCharger->ChargeWithFeetFlat();
	}
private:
	OwnCharger* m_pCharger;
};


#endif