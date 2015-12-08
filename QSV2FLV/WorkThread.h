#pragma once
#include "Thread.h"
#include "ProcessMemory.h"
#include "QiyiPlayer.h"
#include "QiyiFile.h"
#include "FlvFile.h"

class CWorkThread : public CThread
{
public:
	CWorkThread(void);
	~CWorkThread();

	void SetHandleWnd(CWnd *pWnd);
	void SetOutputPath(LPCTSTR pzPath);
	void StartTask(LPCTSTR pzFileName);
	void EndTask();

private:
	//��������ļ���
	CString GetOutputName();	
	BOOL ProcessFile(QIYI_INFO* pInfo, INT nSection);

	//���Ի�����麯��
	virtual DWORD Run();
	virtual void  OnTerminate();

private:
	CWnd*	m_pWnd;
	CString m_szOutputPath;
	CString m_szFileName;

	CQiyiPlayer    m_qiyiPlayer;
	CProcessMemory m_procMem;

	CFlvFile	   m_flvFile;
	CQiyiFile      m_qiyiFile;
};

CWorkThread* GetWorkThread();

//��ʼ wParam=0     lParam=0
#define WTM_START	WM_USER + 100

//���� wParam=0		lParam=ת������*10(%)
#define WTM_PROC	WM_USER + 101
#define WTS_WAIT_PLAY	0	//�ȴ�����
#define WTS_FIND_MEM	1	//�����ڴ�
#define	WTS_LOAD_QIYI	2	//����
#define WTS_BIND_FILE	3	//�����ļ�

//��� wParam=0		lParam=ת��������
#define WTM_RESULT	WM_USER + 102
#define WTE_NONE			0	//û�д���
#define WTE_OPEN_ERROR		1	//���ڴ�ʧ��
#define WTE_WAIT_TIMEOUT	2	//�ȴ����ų�ʱ
#define WTE_FIND_FAIL		3	//�����ڴ�FLVƥ��ʧ��
#define WTE_OPENFILE_FAIL	4	//���ļ�ʧ��
#define WTE_MALLOC_FAIL		5	//�ڴ治��
#define WTE_CREATE_FAIL		6	//����FLVʧ��
#define WTE_FLV_INVALID		7	//FLV��Ч����

//ֹͣ wParam=0		lParam=0
#define WTM_STOP	WM_USER + 103
