
#include "BridgeMain.h"

void BrideMain()
{
	IElectricalEquipment* light = new Light();
	IElectricalEquipment* fan = new Fan();
	
	ISwitch* pullChain = new PullChainSwitch(light);
	ISwitch* twoPosition = new TwoPositionSwitch(fan);
	
	pullChain->On();
	pullChain->Off();

	twoPosition->On();
	twoPosition->Off();

	SAFE_DELETE(twoPosition);
	SAFE_DELETE(pullChain);
	SAFE_DELETE(fan);
	SAFE_DELETE(light);
}