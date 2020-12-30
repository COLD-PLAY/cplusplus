
#ifndef DESIGNPATTERN_OBSERVER_H
#define DESIGNPATTERN_OBSERVER_H

class IObserver
{
public:
	virtual void Update(double price) = 0;
};

#endif