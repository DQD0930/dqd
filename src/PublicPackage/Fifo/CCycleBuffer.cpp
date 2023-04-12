#include "CCycleBuffer.h"

#include <assert.h>
#include <memory.h>

using namespace std;

CCycleBuffer::CCycleBuffer(int size)
{
    m_nBufSize = size;
    m_nReadPos = 0;
    m_nWritePos = 0;
    m_pBuf = new char[m_nBufSize];
    m_bEmpty = true;
    m_bFull = false;
    test = 0;
}

CCycleBuffer::CCycleBuffer(unsigned int baseAddr, int size)
{
    m_nBufSize = size;
    m_nReadPos = 0;
    m_nWritePos = 0;
    //m_pBuf = new char[m_nBufSize];
    m_pBuf = (char*)baseAddr;
    m_bEmpty = true;
    m_bFull = false;
    test = 0;
}

CCycleBuffer::~CCycleBuffer()
{
    delete[] m_pBuf;
}
/************************************************************************/
/* 向缓冲区写入数据，返回实际写入的字节数                               */
/************************************************************************/
int CCycleBuffer::write(char* buf, int count)
{
    int m_nReadPos;
    m_nReadPos = (int)this->m_nReadPos;
    if (count <= 0)
        return 0;
    // 缓冲区已满，不能继续写入 
    if (m_bFull)
    {
        return 0;
    }
    else if (m_nReadPos == m_nWritePos)// 缓冲区为空时 
    {
        /*            == 内存模型 ==
        |←              m_nBufSize                →|
        |← (empty)→  ←                 (empty)  →|
        |------------||------------------------------|
                     ↑←       leftcount          →|           
                   m_nReadPos    
                   m_nWritePos
        */
        int leftcount = m_nBufSize - m_nWritePos;
        if (leftcount > count)
        {
        	m_mutex.lock();
            memcpy(m_pBuf + m_nWritePos, buf, count);
            m_nWritePos += count;
            m_bFull = (this->m_nReadPos == m_nWritePos);
            m_mutex.unlock();
            m_bEmpty = false;
            return count;
        }
        else
        {
            int tmp;
            int leftcount2=0;
            m_mutex.lock();
            memcpy(m_pBuf + m_nWritePos, buf, leftcount);
            tmp = count - leftcount;
            leftcount2 = (m_nReadPos > tmp) ? tmp : m_nReadPos;
            memcpy(m_pBuf, buf + leftcount, leftcount2);
            m_nWritePos = leftcount2;
            m_bFull = (this->m_nReadPos == m_nWritePos);
            m_mutex.unlock();
            m_bEmpty = false;
            return leftcount + m_nWritePos;
        }
    }
    else if (m_nReadPos < m_nWritePos)// 有剩余空间可写入 
    {
        /*            == 内存模型 ==   
        |←              m_nBufSize                →|
        |← (empty)→  ← (data)  →  ←  (empty)  →|
        |------------||xxxxxxxxxxxxx||---------------|
                     ↑                   ↑← leftcount →|  
                   m_nReadPos    m_nWritePos       
        */
        // 剩余缓冲区大小(从写入位置到缓冲区尾) 

        int leftcount = m_nBufSize - m_nWritePos;
        int test = m_nWritePos;
        if (leftcount > count)   // 有足够的剩余空间存放 
        {
        	m_mutex.lock();
            memcpy(m_pBuf + m_nWritePos, buf, count);
            m_nWritePos += count;
            m_bFull = (this->m_nReadPos == m_nWritePos);
            m_mutex.unlock();
            m_bEmpty = false;
            return count;
        }
        else       // 剩余空间不足 
        {
            // 先填充满剩余空间，再回头找空间存放
            int tmp;
            int leftcount2=0;
            m_mutex.lock();
            memcpy(m_pBuf + test, buf, leftcount);
            tmp = count - leftcount;
            leftcount2 = (m_nReadPos > tmp) ? tmp : m_nReadPos;
            memcpy(m_pBuf, buf + leftcount, leftcount2);
            m_nWritePos = leftcount2;
            m_bFull = (this->m_nReadPos == m_nWritePos);
            m_mutex.unlock();
            m_bEmpty = false;
            return leftcount + m_nWritePos;
        }
    }
    else
    {

        /*            == 内存模型 ==
        |←              m_nBufSize                  →|
        |← (data) →  ←  (empty)  →  ←  (data)   →|
        |xxxxxxxxxxxx||---------------||xxxxxxxxxxxxxxx|
        |             ↑← leftcount →↑               |
                   m_nWritePos    m_nReadPos    
        */
        int leftcount = m_nReadPos - m_nWritePos;
        if (leftcount > count)
        {
        	m_mutex.lock();
            // 有足够的剩余空间存放 
            memcpy(m_pBuf + m_nWritePos, buf, count);
            m_nWritePos += count;
            m_bFull = (this->m_nReadPos == m_nWritePos);
            m_mutex.unlock();
            m_bEmpty = false;
            return count;
        }
        else
        {
        	m_mutex.lock();
            // 剩余空间不足时要丢弃后面的数据 
            memcpy(m_pBuf + m_nWritePos, buf, leftcount);
            m_nWritePos += leftcount;
            m_bFull = (this->m_nReadPos == m_nWritePos);
            m_mutex.unlock();
            m_bEmpty = false;
            return leftcount;
        }
    }
}
/************************************************************************/
/* 从缓冲区读数据，返回实际读取的字节数                                 */
/************************************************************************/
int CCycleBuffer::read(char* buf, int count)
{
    int m_nWritePos;
    m_nWritePos = (int)this->m_nWritePos;
    if (count <= 0)
        return 0;
    //m_bFull = false;
    if (m_bEmpty)       // 缓冲区空，不能继续读取数据 
    {
        return 0;
    }
    else if (m_nReadPos == m_nWritePos)   // 缓冲区满时 
    {
        /*            == 内存模型 ==
        |←              m_nBufSize                  →|
        |← (data) →  ←                   (data)   →|
        |xxxxxxxxxxxx||xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx|
        |             ↑← leftcount                  →|
                   m_nWritePos 
                   m_nReadPos
        */
        int leftcount = m_nBufSize - m_nReadPos;
        if (leftcount > count)
        {
        	m_mutex.lock();
            memcpy(buf, m_pBuf + m_nReadPos, count);
            m_nReadPos += count;
            m_bEmpty = (m_nReadPos == this->m_nWritePos);
            m_mutex.unlock();
            m_bFull = false;
            return count;
        }
        else
        {
            int tmp;
            int leftcount2;
            m_mutex.lock();
            memcpy(buf, m_pBuf + m_nReadPos, leftcount);
            tmp = count - leftcount;
            leftcount2 = (m_nWritePos > tmp) ? tmp : m_nWritePos;
            memcpy(buf + leftcount, m_pBuf, leftcount2);
            m_nReadPos = leftcount2;
            m_bEmpty = (m_nReadPos == this->m_nWritePos);
            m_mutex.unlock();
            m_bFull = false;
            return leftcount + m_nReadPos;
        }
    }
    else if (m_nReadPos < m_nWritePos)   // 写指针在前(未读数据是连接的) 
    {
        /*            == 内存模型 ==
        |←              m_nBufSize                  →|
        |← (empty)→  ← (data)    →  ←  (empty)  →|
        |------------||xxxxxxxxxxxxxxx||---------------|
                     ↑← leftcount →↑               |
                   m_nReadPos    m_nWritePos
        */
        int leftcount = m_nWritePos - m_nReadPos;
        int c = (leftcount > count) ? count : leftcount;
        m_mutex.lock();
        memcpy(buf, m_pBuf + m_nReadPos, c);
        m_nReadPos += c;
        m_bEmpty = (m_nReadPos == this->m_nWritePos);
        m_mutex.unlock();
        m_bFull = false;
        return c;
    }
    else          // 读指针在前(未读数据可能是不连接的) 
    {
        /*            == 内存模型 ==
        |←              m_nBufSize                  →|
        |← (data) →  ←  (empty)  →  ←  (data)   →|
        |xxxxxxxxxxxx||---------------||xxxxxxxxxxxxxxx|
        |             ↑               ↑← leftcount →|
                   m_nWritePos    m_nReadPos
        */
        int leftcount = m_nBufSize - m_nReadPos;
        if (leftcount > count)   // 未读缓冲区够大，直接读取数据 
        {
        	m_mutex.lock();
            memcpy(buf, m_pBuf + m_nReadPos, count);
            m_nReadPos += count;
            m_bEmpty = (m_nReadPos == this->m_nWritePos);
            m_mutex.unlock();
            m_bFull = false;
            return count;
        }
        else       // 未读缓冲区不足，需回到缓冲区头开始读 
        {
            memcpy(buf, m_pBuf + m_nReadPos, leftcount);
            int tmp;
            int leftcount2;
            m_mutex.lock();
            tmp = count - leftcount;
            leftcount2 = (m_nWritePos > tmp) ? tmp : m_nWritePos;
            memcpy(buf + leftcount, m_pBuf, leftcount2);
            m_nReadPos = leftcount2;
            m_bEmpty = (m_nReadPos == this->m_nWritePos);
            m_mutex.unlock();
            m_bFull = false;
            return leftcount + m_nReadPos;
        }
    }
}
/************************************************************************/
/* 获取缓冲区有效数据长度                                               */
/************************************************************************/
int CCycleBuffer::getReadableLength()
{
    if (m_bEmpty)
    {
        return 0;
    }
    else if (m_bFull)
    {
        return m_nBufSize;
    }
    else if (m_nReadPos < m_nWritePos)
    {
        return m_nWritePos - m_nReadPos;
    }
    else
    {
        return m_nBufSize - m_nReadPos + m_nWritePos;
    }
}

int CCycleBuffer::getWriteableLength()
{
    return m_nBufSize-getReadableLength();
}

void CCycleBuffer::empty()
{
    m_nReadPos = 0;
    m_nWritePos = 0;
    m_bEmpty = true;
    m_bFull = false;
}

bool CCycleBuffer::isEmpty()
{
    return m_bEmpty;
}

bool CCycleBuffer::isFull()
{
    return m_bFull;
}
