
#ifndef DESIGNPATTERN_BRIDGEMAIN_H
#define DESIGNPATTERN_BRIDGEMAIN_H

#include "ConcreteImplementor.h"
#include "RefinedAbstraction.h"

#ifndef SAFE_DELETE
#define SAFE_DELETE(p) { if (p) { delete(p); (p) = nullptr; } }
#endif

void BridgeMain();

#endif