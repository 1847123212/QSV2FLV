// QSV2FLV.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CQSV2FLVApp:
// �йش����ʵ�֣������ QSV2FLV.cpp
//

class CQSV2FLVApp : public CWinApp
{
public:
	CQSV2FLVApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CQSV2FLVApp theApp;