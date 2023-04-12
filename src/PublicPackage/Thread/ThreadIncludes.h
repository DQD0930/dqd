#ifndef THREAD_INCLUDES_H_
#define THREAD_INCLUDES_H_

#include "Thread.h"

#ifdef LINUX
#include "OSRelative/Linux/LinuxThread.h"
#endif

#ifdef WIN32
#include "OSRelative/Windows/WindowsThread.h"
#endif

#endif
