#pragma once

#include <wtypes.h>

//�ӿ���
class IMyLock
{
public:
	virtual ~IMyLock(){};
	virtual void Lock() const = 0;
	virtual void Unlock() const = 0;
};
//�����������
class CMutex : public IMyLock
{
public:
	CMutex(BOOL bInitialOwner = FALSE, LPCTSTR lpName = NULL)
	{
		//HANDLE CreateMutex(
		//	LPSECURITY_ATTRIBUTES lpMutexAttributes,  // SD
		//	BOOL bInitialOwner,                       // initial owner
		//	LPCTSTR lpName                            // object name
		//	);

		m_mutex = ::CreateMutex(NULL, bInitialOwner, lpName);
	}
	~CMutex()
	{
		if (NULL != m_mutex)
			::CloseHandle(m_mutex);
	}
	virtual void Lock() const
	{
		::WaitForSingleObject(m_mutex, INFINITE);
	}
	virtual void Unlock() const
	{
		::ReleaseMutex(m_mutex);
	}
private:
	HANDLE m_mutex;
};
//��
class CLock
{
public:
	CLock(const IMyLock& lock) : m_lock(lock)
	{
		m_lock.Lock();
	}
	~CLock()
	{
		m_lock.Unlock();
	}
private:
	const IMyLock& m_lock;
};