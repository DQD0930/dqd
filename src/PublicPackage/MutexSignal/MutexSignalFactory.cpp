// MutexSignalFactory.cpp: implementation of the CMutexSignalFactory class.
//
//////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include "stdef.h"
#include "EventLock.h"
#include "MutexLock.h"
#include "SemaphoreLock.h"
#include "MutexSignalFactory.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CMutexSignalFactory* CMutexSignalFactory::m_pMutexSignalFactory = NULL;

CMutexSignalFactory::CMutexSignalFactory()
{

}

CMutexSignalFactory::~CMutexSignalFactory()
{

}
