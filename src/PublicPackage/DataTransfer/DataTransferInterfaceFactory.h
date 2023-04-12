// TransferInterfaceFactory.h: interface for the CTransferInterfaceFactory class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TRANSFERINTERFACEFACTORY_H__33B5176D_3D31_4BC4_B558_9B75C2C91B88__INCLUDED_)
#define AFX_TRANSFERINTERFACEFACTORY_H__33B5176D_3D31_4BC4_B558_9B75C2C91B88__INCLUDED_

#include <stdef.h>
#include <Thread.h>


#include "DataTransferInterface.h"
class CDataTransferInterfaceFactory
{
public:
	virtual ~ CDataTransferInterfaceFactory();


protected:
  CThread *m_pThread;
protected:
  CDataTransferInterfaceFactory ();
  //Attention: Here pInterface MUST be allocated in heap!(new ****)
  CDataTransferInterface* DataTransferInterfaceStartWork(CDataTransferInterface *pInterface);
};

#endif // !defined(AFX_TRANSFERINTERFACEFACTORY_H__33B5176D_3D31_4BC4_B558_9B75C2C91B88__INCLUDED_)
