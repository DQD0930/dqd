#ifndef _CLK_BUFFER_H
#define _CLK_BUFFER_H

#include "stdef.h"
#include "MutexSignalIncludes.h"

#define HEADER_DATA_LEN		100
#define TAIL_DATA_LEN		100
#define CTRL_DATA_LEN		32

struct lk_buffer_header {
	struct lk_buffer *prev;
	struct lk_buffer *next;
	int qlen;
};

struct lkb_shared_info {
	class CLkBuffer *master;
	unsigned char nullflag;
	char ctrldata[CTRL_DATA_LEN];
};

struct lk_buffer {
	struct lk_buffer_header *list;
	struct lk_buffer *prev;
	struct lk_buffer *next;
	int datalen;
	char mode;
	unsigned char *header;
	unsigned char *data;
	unsigned char *tail;
	struct lkb_shared_info *lkb_shared_info;
};

enum return_type{
	RETURN_TYPE_OK = 0x00,
	RETURN_TYPE_ERR,
};

class CLkBuffer {
private:
    CMutexLock *m_pUsedMutex;
	CMutexLock *m_plkMutex;
    CSemaphoreLock *m_plock;
    CMutexSignalFactory *m_pMutexSignalFactory;
    void create_header();
    char isnull();
protected:
	struct lk_buffer *m_plkbh;
    int m_nqlen;
public:
	CLkBuffer();
	~CLkBuffer();
	return_type create(CLkBuffer *pmaster , CMutexSignalFactory *pMutexSignalFactory , int lockinit , int lockmax , int num = 0, int len = 0);
	void push_front(struct lk_buffer *lkb);
	void push_front_init(struct lk_buffer *lkb);
	struct lk_buffer *back();

	struct lk_buffer *lk_put(struct lk_buffer *lkb , int len);
	struct lk_buffer *lk_push(struct lk_buffer *lkb , int len);
	struct lk_buffer *lk_pull(struct lk_buffer *lkb , int len);
	struct lk_buffer *lk_pop(struct lk_buffer *lkb , int len);
	struct lk_buffer *lk_reserver(struct lk_buffer *lkb , int len);

	int size();
	int GetLastBufDataLen();
};


#endif