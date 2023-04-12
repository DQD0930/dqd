#ifndef MUTEXSIGNAL_INCLUDES_H_
#define MUTEXSIGNAL_INCLUDES_H_

#include "MutexLock.h"
#include "SemaphoreLock.h"
#include "EventLock.h"
#include "MutexSignalFactory.h"

#ifdef LINUX
#include <pthread.h>
#include <semaphore.h>
#include <time.h>
#include <errno.h>
#include "OSRelative/Linux/LinuxMutexLock.h"
#include "OSRelative/Linux/LinuxSemaphoreLock.h"
#include "OSRelative/Linux/LinuxEventLock.h"
#include "OSRelative/Linux/LinuxMutexSignalFactory.h"
#endif

#ifdef WIN32
#include "OSRelative/Windows/WinMutexLock.h"
#include "OSRelative/Windows/WinSemaphoreLock.h"
#include "OSRelative/Windows/WinEventLock.h"
#include "OSRelative/Windows/WinMutexSignalFactory.h"
#endif

#endif
