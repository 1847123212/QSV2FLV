#include "StdAfx.h"
#include "QiyiPlayer.h"
#include "FindAllWindow.h"

//2013.12.12
//��ǰ�������հ汾2.10.0.10
//QiyiClient.exe����������
//QiyiPlayer.exe�������Ŵ���

BOOL CQiyiPlayer::Play(LPCTSTR pzFileName)
{
	m_nPidPlayer = 0;
	m_hWndClient = NULL;
	m_hWndPlayer = NULL;
	ShellExecute(NULL, L"open", pzFileName, NULL, NULL, SW_SHOW);
	return WaitForPlay(10);
}

//�˳�����
//WM_USER+787 0x80 0x204
//WM_COMMAND 0x8008 0x0
void CQiyiPlayer::Close()
{
	//if (m_hWndPlayer)
	//	::PostMessage(m_hWndPlayer, WM_QUIT, 0, 0);
	
	CString szParam;
	szParam.Format(_T("/pid %d"), m_nPidPlayer);
	ShellExecute(NULL, L"open", _T("taskkill"), szParam, NULL, SW_HIDE);

	if (m_hWndClient)
		::PostMessage(m_hWndClient, WM_COMMAND, 0x8008, 0x0);

	//�ȴ����Ŵ����˳�
	::Sleep(3000);
}


//"��������Ƶ����"
//"RenderWindow"
BOOL CQiyiPlayer::WaitForPlay(INT nTimeout)
{
	INT  nWait = 0;
	while(nWait < nTimeout)	//�ȴ���ʱ
	{
		nWait++;
		::Sleep(500);
		if (!m_hWndClient)
			m_hWndClient = ::FindAllWindow(NULL, _T("��������Ƶ"));
		
		//if (!m_hWndPlayer)
		//	m_hWndPlayer = ::FindAllWindow(NULL, _T("��������Ƶ����"));

		m_nPidPlayer = ::GetProcessID(_T("QiyiPlayer.exe"));
		if(m_hWndClient && m_nPidPlayer)
		{
			::Sleep(2000);
			return TRUE;
		}
	}
	return FALSE;
}
