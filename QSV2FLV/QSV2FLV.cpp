// QSV2FLV.cpp : ����Ӧ�ó��������Ϊ��
//
#include "stdafx.h"
#include "QSV2FLV.h"
#include "QSV2FLVDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CQSV2FLVApp
BEGIN_MESSAGE_MAP(CQSV2FLVApp, CWinApp)
END_MESSAGE_MAP()


// CQSV2FLVApp ����
CQSV2FLVApp::CQSV2FLVApp()
{
	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CQSV2FLVApp ����
CQSV2FLVApp theApp;


// CQSV2FLVApp ��ʼ��
BOOL CQSV2FLVApp::InitInstance()
{
	CWinApp::InitInstance();
	CQSV2FLVDlg dlg;
	m_pMainWnd = &dlg;
	dlg.DoModal();
	return FALSE;
}
