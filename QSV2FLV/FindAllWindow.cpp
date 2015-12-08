#include "StdAfx.h"
#include <TlHelp32.h>
#include "FindAllWindow.h"


BOOL CALLBACK EnumWindowProc(HWND hWnd, LPARAM lParam);

static CString g_szClassName;
static CString g_szWindowName;

//���������Ӵ���,��ȱ���
HWND FindAllWindow(LPCTSTR lpClassName, LPCTSTR lpWindowName)
{
	HWND hWnd = NULL;
	g_szClassName = lpClassName;
	g_szWindowName= lpWindowName; 
	::EnumWindows(EnumWindowProc, (LPARAM)&hWnd);
	return hWnd;
}


//����TRUE�������
//����FALSE����ֹͣ����
BOOL CALLBACK EnumWindowProc(HWND hWnd, LPARAM lParam)
{
	TCHAR szText[MAX_PATH];
	::GetWindowText(hWnd, szText, MAX_PATH);
	if (g_szWindowName == szText)
	{
		OutputDebugString(szText);
		OutputDebugString(_T("\n"));
		*((HWND*)lParam) = hWnd;
		return FALSE;
	}
	::EnumChildWindows(hWnd, EnumWindowProc, lParam);
	return TRUE;
}



//���ݽ����������ص�һ������ʵ����PID
INT GetProcessID(LPCTSTR pzProcessName)
{	
	BOOL bRet;
	CString szExeName(pzProcessName);
	HANDLE hProcess;
	PROCESSENTRY32 procEntry;
	procEntry.dwSize = sizeof(PROCESSENTRY32); 

	//���н��̿���
	hProcess=CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);
	//��ʼ���̲���
	bRet=Process32First(hProcess,&procEntry);

	//ѭ���Ƚϣ��ó�ProcessID
	while(bRet)
	{
		if(0 == szExeName.Compare(procEntry.szExeFile))
			return procEntry.th32ProcessID;
		bRet=Process32Next(hProcess,&procEntry);
	}
	return 0;
}
