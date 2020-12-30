
#ifndef DESIGNPATTERN_SINGLETONMAIN_H
#define DESIGNPATTERN_SINGLETONMAIN_H

#include "Singleton.h"

void SingletonMain()
{
	Singleton::GetInstance().DoSomething();
}

#endif