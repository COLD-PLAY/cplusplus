
#ifndef DESIGNPATTERN_CONCRETE_OBSERVER_H
#define DESIGNPATTERN_CONCRETE_OBSERVER_H

#include "Observer.h"

#include <iostream>
#include <string>

using namespace std;

class ConcreteObserver : public IObserver
{
public:
	ConcreteObserver(string name) : m_strName(name) {}
	
	virtual void Update(double price) override
	{
		cout << m_strName << " - price " << price << endl;
	}

private:
	string m_strName;
};

#endif