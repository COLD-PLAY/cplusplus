
#ifndef DESIGNPATTERN_ADAPTEE_H
#define DESIGNPATTERN_ADAPTEE_H

#include <iostream>

using namespace std;

class OwnCharger
{
public:
	void ChargeWithFeetFlat()
	{
		cout << "OwnCharger::ChargeWithFeetFlat" << endl;
	}
};

#endif