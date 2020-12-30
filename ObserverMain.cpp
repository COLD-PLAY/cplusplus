
#include "ObserverMain.h"

void ObserverMain()
{
	ConcreteSubject* pSubject = new ConcreteSubject();
	
	IObserver* pObserver1 = new ConcreteObserver("Liao Zhou");
	IObserver* pObserver2 = new ConcreteObserver("Sun Xun");
	
	pSubject->Attach(pObserver1);
	pSubject->Attach(pObserver2);

	pSubject->SetPrice(23.3);
	pSubject->Notify();

	pSubject->Detach(pObserver1);

	pSubject->SetPrice(19.9);
	
}