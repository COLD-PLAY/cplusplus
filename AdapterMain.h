
#ifndef DESIGNPATTERN_ADAPTERMAIN_H
#define DESIGNPATTERN_ADAPTERMAIN_H

#include "Adapter.h"

void AdapterMain()
{
	IRussiaSockt* pAdapter = new PowerAdapter();
	
	pAdapter->Charge();

	SAFE_DELETE(pAdapter);
}

#endif