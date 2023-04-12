#include <stddef.h>
#include <stdio.h>
#include "CLkBuffer.h"

CLkBuffer::CLkBuffer()
{

}

CLkBuffer::~CLkBuffer()
{
	lk_buffer *dlkb = NULL;
	if (m_plkbh == NULL)
		return;
	while (m_plkbh->next != NULL)
	{
		dlkb = m_plkbh->next;
		if (dlkb->header)
			delete dlkb->header;
		m_plkbh->next = dlkb->next;
		delete dlkb; 
	}
}

void CLkBuffer::create_header()
{
	m_plkbh = new lk_buffer{0};
	m_plkbh->next = m_plkbh;
	m_plkbh->prev = m_plkbh;
}

return_type CLkBuffer::create(CLkBuffer *pmaster , CMutexSignalFactory *pMutexSignalFactory , int lockinit , int lockmax , int num, int len)
{
	lk_buffer *nlkb = NULL;
	
	m_pMutexSignalFactory = pMutexSignalFactory;
	m_plkbh = NULL;
    m_nqlen = 0;

	create_header();

    m_pUsedMutex = m_pMutexSignalFactory->CreateMutexLock();
	m_plkMutex= m_pMutexSignalFactory->CreateMutexLock();
    m_plock = m_pMutexSignalFactory->CreateSemaphoreLock(lockinit,lockmax);

	for (int i = 0; i < num; i++)
	{
		nlkb = new lk_buffer{0};
		
		nlkb->header = new unsigned char[len + HEADER_DATA_LEN + TAIL_DATA_LEN];
		nlkb->data = nlkb->header + HEADER_DATA_LEN;
		nlkb->tail = (nlkb->data + nlkb->datalen);
		nlkb->lkb_shared_info = (lkb_shared_info *)(nlkb->header + HEADER_DATA_LEN + len);

		if (nlkb->header == NULL)
		{
			printf("malloc mem faild\r\n");
			return RETURN_TYPE_ERR;
		}

		if(pmaster != NULL)
			nlkb->lkb_shared_info->master = pmaster;
		push_front(nlkb);
	}
	return RETURN_TYPE_OK;
}

void CLkBuffer::push_front(lk_buffer *lkb)
{
	if (m_plkbh == NULL)
		return ;

    m_pUsedMutex->Lock();
	lk_buffer *tail = m_plkbh->next;
	
	m_plkbh->next = lkb;
    tail->prev = lkb;
    lkb->prev = m_plkbh;
    lkb->next = tail;

    m_nqlen++;
    m_pUsedMutex->Unlock();
    m_plock->Unlock();
}

void CLkBuffer::push_front_init(struct lk_buffer *lkb)
{
	lkb->datalen = 0;
	lkb->data = lkb->header + HEADER_DATA_LEN;
	lkb->tail = (lkb->data + lkb->datalen);
	memset(lkb->lkb_shared_info->ctrldata , 0x00 , CTRL_DATA_LEN);
	push_front(lkb);
}

lk_buffer *CLkBuffer::back()
{
	struct lk_buffer *out = NULL;
	m_plock->Lock();
	if (isnull())
		return NULL;
    m_pUsedMutex->Lock();
	out = m_plkbh->prev;
	m_plkbh->prev = out->prev;
	out->prev->next = m_plkbh;
	m_nqlen--;
    m_pUsedMutex->Unlock();
	return out;
}

struct lk_buffer *CLkBuffer::lk_put(struct lk_buffer *lkb , int len)
{
	lkb->data -= len;
	lkb->datalen += len;
	return lkb;
}

struct lk_buffer *CLkBuffer::lk_push(struct lk_buffer *lkb , int len)
{
	lkb->datalen += len;
	lkb->tail = (lkb->data + lkb->datalen);
	return lkb;
}

struct lk_buffer *CLkBuffer::lk_pull(struct lk_buffer *lkb , int len)
{
	lkb->datalen -= len;
	lkb->tail = (lkb->data + lkb->datalen);
	return lkb;
}

struct lk_buffer *CLkBuffer::lk_pop(struct lk_buffer *lkb , int len)
{
	lkb->data += len;
	lkb->datalen -= len;
	lkb->tail = (lkb->data + lkb->datalen);
	return lkb;
}

struct lk_buffer *CLkBuffer::lk_reserver(struct lk_buffer *lkb , int len)
{
	lkb->data = lkb->header + HEADER_DATA_LEN;
	lkb->datalen = len;
	lkb->tail = (lkb->data + lkb->datalen);
}

int CLkBuffer::size()
{
	return m_nqlen;
}

char CLkBuffer::isnull()
{
    if((m_plkbh->prev==m_plkbh->next) && (m_plkbh->prev == m_plkbh))
        return 1;
    return 0;
}

int CLkBuffer::GetLastBufDataLen()
{
	struct lk_buffer *out = NULL;
	out = m_plkbh->prev;
	return out->datalen;
}