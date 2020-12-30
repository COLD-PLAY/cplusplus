
#ifndef DESIGNPATTERN_OBSERVERMAIN_H
#define DESIGNPATTERN_OBSERVERMAIN_H

#include "ConcreteObserver.h"
#include "ConcreteSubject.h"

#ifndef SAFE_DELETE
#define SAFE_DELETE(p) { if (p) { delete(p); (p) = nullptr; } }
#endif

void ObserverMain();

#endif