
#ifndef DESIGNPATTERN_CONCRETE_SUBJECT_H
#define DESIGNPATTERN_CONCRETE_SUBJECT_H

#include "Subject.h"

#include <iostream>
#include <list>

#include "Observer.h"

using namespace std;

class ConcreteSubject : public ISubject
{
public:
	ConcreteSubject() : m_dPrice(10.0) {}

	void SetPrice(double price)
	{
		m_dPrice = price;
	}

	virtual void Attach(IObserver* pObserver)
	{
		m_lObservers.push_back(pObserver);
	}

	virtual void Detach(IObserver* pObserver)
	{
		m_lObservers.remove(pObserver);
	}

	virtual void Notify()
	{
		auto it = m_lObservers.begin();
		while (it != m_lObservers.end())
		{
			(*it)->Update(m_dPrice);
			it++;
		}
	}

private:
	list<IObserver*> m_lObservers;
	double m_dPrice;
};

#endif