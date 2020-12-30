
#ifndef DESIGNPATTERN_SUBJECT_H
#define DESIGNPATTERN_SUBJECT_H

class IObserver;

class ISubject
{
public:
	virtual void Attach(IObserver*) = 0;
	virtual void Detach(IObserver*) = 0;
	virtual void Notify() = 0;
};

#endif