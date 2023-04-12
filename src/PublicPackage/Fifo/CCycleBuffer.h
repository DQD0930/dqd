#ifndef CCYCLEBUFFER_H_
#define CCYCLEBUFFER_H_

using namespace std;

#include <mutex>

class CCycleBuffer
{
public:
    bool isFull();
    bool isEmpty();
    void empty();
    int getReadableLength();
    int getWriteableLength();
    CCycleBuffer(int size);
    CCycleBuffer(unsigned int baseAddr, int size);
    virtual~CCycleBuffer();
    int write(char* buf, int count);
    int read(char* buf, int count);
    int getStart()
    {
        return m_nReadPos;
    }
    int getEnd()
    {
        return m_nWritePos;
    }

private:
    bool m_bEmpty, m_bFull;
    char* m_pBuf;
    int m_nBufSize;
    int m_nReadPos;
    int m_nWritePos;
    mutex m_mutex;
    int test;
};

#endif


