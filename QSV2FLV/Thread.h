#ifndef _THREAD_H_
#define _THREAD_H_

/**
*@class CThread
*@brief �߳�
*
*��Ҫ���ڼ򻯿��̵߳ĸ��Ӷȡ�
*/
class CThread
{
public:
	CThread();
	virtual ~CThread();

public:
	HANDLE		m_hThread;

public:
	/**
	*@brief	�����߳�
	*@return	
	*- TRUE	�߳̿����ɹ�
	*- FALSE�߳̿���ʧ��
	*/
	BOOL Start();

	/**
	*@brief	�̶߳�������װ���߳��Ƿ�͵��ø÷������߳�Ϊͬһ�̡߳�
	*@return	
	*- TRUE	��
	*- FALSE��
	*/
	BOOL IsCurrent() { return (m_dwThreadID == Self()); }

	/** 
	*@brief	�̶߳�������װ���߳��Ƿ���������
	*@return	
	*- TRUE	��������
	*- FALSE�Ѿ�ֹͣ����
	*/
	BOOL IsRuning() { return (NULL != m_hThread); }

	/** 
	*@brief	��ֹһ���߳�
	*/
	void Terminate();

	/** 
	*@brief	�õ������߳�ID
	*@return �߳�ID
	*/
	static DWORD Self();

	/**
	*@brief	�߳�ִ���壬��һ�����󷽷�����������ʵ��
	*@return �̵߳ķ���ֵ
	*/
	virtual DWORD Run() = 0;

	/**
	*@brief	�߳̽�����ʱ�򱻵��õķ���, �ɾ���������������ô����
	*@return �޷���ֵ
	*/
	virtual void OnTerminate(){}

private:
	typedef unsigned (WINAPI *PTHREAD_START) (void *);

private:
	friend DWORD WINAPI Runner(void* arg);

private:
	DWORD 		m_dwThreadID;
};

#endif 
