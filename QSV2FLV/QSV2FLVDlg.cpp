// QSV2FLVDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "QSV2FLV.h"
#include "QSV2FLVDlg.h"
#include "AboutDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CQSV2FLVDlg �Ի���
#define DEFAULT_PATH	_T("D:\\")

CQSV2FLVDlg::CQSV2FLVDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CQSV2FLVDlg::IDD, pParent)
	, m_szPath(DEFAULT_PATH)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CQSV2FLVDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ctrlList);
	DDX_Text(pDX, IDC_EDIT1, m_szPath);
}

BEGIN_MESSAGE_MAP(CQSV2FLVDlg, CDialog)
	ON_BN_CLICKED(IDC_BTN_ADD, &CQSV2FLVDlg::OnBnClickedBtnAdd)
	ON_BN_CLICKED(IDC_BTN_DEL, &CQSV2FLVDlg::OnBnClickedBtnDel)
	ON_BN_CLICKED(IDC_BTN_START, &CQSV2FLVDlg::OnBnClickedBtnStart)
	ON_BN_CLICKED(IDC_BTN_STOP, &CQSV2FLVDlg::OnBnClickedBtnStop)
	ON_BN_CLICKED(IDC_BTN_ABOUT, &CQSV2FLVDlg::OnBnClickedBtnAbout)
	ON_BN_CLICKED(IDC_BTN_PATH, &CQSV2FLVDlg::OnBnClickedBtnPath)
	ON_BN_CLICKED(IDC_BTN_OPENPATH, &CQSV2FLVDlg::OnBnClickedBtnOpenpath)
	ON_WM_TIMER()
	//�߳���Ϣ
	ON_MESSAGE(WTM_START, OnWorkThreadStart)
	ON_MESSAGE(WTM_PROC, OnWorkThreadProc)
	ON_MESSAGE(WTM_RESULT, OnWorkThreadResult)
	ON_MESSAGE(WTM_STOP, OnWorkThreadStop)
END_MESSAGE_MAP()


// CQSV2FLVDlg ��Ϣ�������

BOOL CQSV2FLVDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	CString szTitle = _T("QSV2FLV ");
	szTitle += STR_VERSION;
	SetWindowText(szTitle);
	m_bmpFold.LoadBitmap(IDB_BITMAP1);
	CButton* pCtrl = (CButton*)GetDlgItem(IDC_BTN_PATH);
	pCtrl->SetBitmap(m_bmpFold);

	//�����б�
	m_ctrlList.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	//�����У���ţ����ƣ����룬�п�
	m_ctrlList.InsertColumn(1,_T("���"),LVCFMT_CENTER, 36);  
	m_ctrlList.InsertColumn(1,_T("�ļ�"),LVCFMT_LEFT,400);  
	m_ctrlList.InsertColumn(2,_T("״̬"),LVCFMT_LEFT,80);

	//��ʼ�������߳�
	m_pWorkThread = ::GetWorkThread();
	m_pWorkThread->SetHandleWnd(this);

	SetWindowPos(&CWnd::wndTopMost, 0,0,0,0, SWP_NOMOVE|SWP_NOSIZE);

	PostMessage(WM_TIMER, 0, 0);
	return TRUE;
}


void CQSV2FLVDlg::OnBnClickedBtnAdd()
{
	// TODO: ����ļ��б�
	CString		szFileName;
	CString		szCount;
	POSITION	pos;
	int			i;
	int			nCount=0;		//�ļ�����
	//�����ļ�
	CFileDialog InFile( TRUE,NULL,NULL,OFN_FILEMUSTEXIST|OFN_ALLOWMULTISELECT,_T("������Ƶ|*.QSV|�����ļ�(*.*)|*.*||") );
	InFile.m_ofn.nMaxFile  = 10000;		//�ļ�����
	InFile.m_ofn.lpstrFile = (LPWSTR)malloc(InFile.m_ofn.nMaxFile*sizeof(TCHAR));
	memset(InFile.m_ofn.lpstrFile,0,InFile.m_ofn.nMaxFile);

	nCount = m_ctrlList.GetItemCount();
	if(InFile.DoModal() == IDOK)
	{
		pos=InFile.GetStartPosition(); 
		while(pos)
		{	
			szFileName=InFile.GetNextPathName(pos);
			m_ctrlList.InsertItem(nCount,  NULL);	//�����
			m_ctrlList.SetItemText(nCount, 1, szFileName);
			m_ctrlList.SetItemText(nCount, 2, TEXT("����") );
			nCount++;
		}
		for(i=0; i<nCount; i++)
		{
			szCount.Format(_T("%d"),i+1);
			m_ctrlList.SetItemText(i,0,szCount);
		}
		GetDlgItem(IDC_BTN_DEL)->EnableWindow(TRUE);	//����START
		GetDlgItem(IDC_BTN_START)->EnableWindow(TRUE);
	}
	free(InFile.m_ofn.lpstrFile);
}

void CQSV2FLVDlg::OnBnClickedBtnDel()
{
	// TODO: ����б�
	if( IDOK==MessageBox(_T("ȷ����������б�"),_T("����б�"), MB_OKCANCEL|MB_ICONQUESTION) )
	{
		m_ctrlList.DeleteAllItems();
		GetDlgItem(IDC_BTN_DEL)->EnableWindow(0);
		GetDlgItem(IDC_BTN_START)->EnableWindow(0);
	}
}

void CQSV2FLVDlg::OnBnClickedBtnStart()
{
	// TODO: ��ʼ
	if (m_ctrlList.GetItemCount() == 0)
	{
		MessageBox(_T("�б�Ϊ��!"), _T("��ʼת��"), MB_OK|MB_ICONINFORMATION);
		return;
	}
	BOOL bRet = m_pWorkThread->Start();
	if (!bRet)
	{
		MessageBox(_T("����ʧ�ܣ����˳�������!"), _T("������"), MB_OK|MB_ICONWARNING);
		return;
	}

	GetDlgItem(IDC_BTN_ADD)->EnableWindow(0);
	GetDlgItem(IDC_BTN_DEL)->EnableWindow(0);
	GetDlgItem(IDC_BTN_START)->EnableWindow(0);
	GetDlgItem(IDC_BTN_STOP)->EnableWindow(1);
}

void CQSV2FLVDlg::OnBnClickedBtnStop()
{
	// TODO:ֹͣ
	INT nRet = MessageBox(_T("���ޱ�Ҫ�벻Ҫǿ��ֹͣ!"), _T("����"), MB_OKCANCEL|MB_ICONWARNING);
	if (nRet == IDOK)
	{
		m_pWorkThread->Terminate();
	}
	Sleep(0);
}

void CQSV2FLVDlg::OnBnClickedBtnAbout()
{
	// TODO: ����
	CAboutDlg dlg;
	dlg.DoModal();
}

void CQSV2FLVDlg::OnBnClickedBtnPath()
{
	// TODO: ѡ�����·��
	TCHAR szDir[MAX_PATH];
	BROWSEINFO bi; 
	ITEMIDLIST *pidl; 
	bi.hwndOwner = this->m_hWnd; 
	bi.pidlRoot = NULL;
	bi.pszDisplayName = szDir; 
	bi.lpszTitle = _T("ѡ������ļ��У�"); 
	bi.ulFlags = BIF_NEWDIALOGSTYLE;//BIF_RETURNONLYFSDIRS; 
	bi.lpfn = NULL;
	bi.lParam = 0;
	bi.iImage = 0;
	pidl = SHBrowseForFolder(&bi); 
	if (pidl == NULL)
		return;
	if(SHGetPathFromIDList(pidl, szDir)) 
		m_szPath = szDir;
	UpdateData(FALSE);
}

void CQSV2FLVDlg::OnBnClickedBtnOpenpath()
{
	// TODO: �����Ŀ¼
	::ShellExecute(NULL, _T("explore"), m_szPath, NULL, NULL, SW_SHOW);
}

void CQSV2FLVDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CString szText;
	szText = _T("����������\nQSV��Ƶ��Ȩ�鰮�������У��������ڷǷ���;!\n");
	szText += _T("\n���ڰ����ո���Ƶ������������ʱ���ܻ�ʧЧ!\nʹ��ǰ��ȷ���Ѱ�װ�����հ汾��2.10.0.10��");
	MessageBox(szText, L"��Ҫ˵��", MB_OKCANCEL|MB_ICONWARNING);
}

//�����߳�����������ʼ��һ������
LRESULT CQSV2FLVDlg::OnWorkThreadStart(WPARAM wParam, LPARAM lParam)
{
	int nFileCount;
	m_pWorkThread->SetOutputPath(m_szPath);
	nFileCount =m_ctrlList.GetItemCount();
	for(m_nCurIndex = 0; m_nCurIndex<nFileCount; m_nCurIndex++)
	{
		CString	szFileStatus = m_ctrlList.GetItemText(m_nCurIndex, 2);
		if (szFileStatus != _T("���"))
		{
			break;
		}
	}
	CString	szFileName = m_ctrlList.GetItemText(m_nCurIndex, 1);
	m_pWorkThread->StartTask(szFileName);
	return 1;
}

//ת������
//wParam=ת��״̬ lParam=ת������*10(%)
LRESULT CQSV2FLVDlg::OnWorkThreadProc(WPARAM wParam, LPARAM lParam)
{
	CString szText;
	FLOAT	fRate;
	switch(wParam)
	{
	case WTS_WAIT_PLAY:		//�ȴ�����
		m_ctrlList.SetItemText(m_nCurIndex, 2, _T("�ȴ�����"));
		break;
	case WTS_FIND_MEM:		//�����ڴ�
		m_ctrlList.SetItemText(m_nCurIndex, 2, _T("���ڷ���"));
		break;
	case WTS_LOAD_QIYI:		//����
		m_ctrlList.SetItemText(m_nCurIndex, 2, _T("��ȡ����"));
		break;
	case WTS_BIND_FILE:		//�����ļ�
		fRate = (FLOAT)lParam / 10;
		szText.Format(_T("%.1f%%"), fRate);
		m_ctrlList.SetItemText(m_nCurIndex, 2, szText);
		break;
	default:
		break;
	}

	return 1;
}

//ת������
//lParam=ת��������
LRESULT CQSV2FLVDlg::OnWorkThreadResult(WPARAM wParam, LPARAM lParam)
{
	INT nFileCount;
	CString szFileName;
	switch(lParam)
	{
	case WTE_NONE:
		m_ctrlList.SetItemText(m_nCurIndex, 2, _T("���"));
		nFileCount = m_ctrlList.GetItemCount();

		//����û��ɵ�
		for(m_nCurIndex++; m_nCurIndex<nFileCount; m_nCurIndex++)
		{
			CString	szFileStatus = m_ctrlList.GetItemText(m_nCurIndex, 2);
			if (szFileStatus != _T("���"))
			{
				break;
			}
		}

		if (m_nCurIndex < nFileCount)
		{
			szFileName = m_ctrlList.GetItemText(m_nCurIndex, 1);
			m_pWorkThread->StartTask(szFileName);
		}
		else
		{
			m_pWorkThread->EndTask();
		}
		break;

	case WTE_WAIT_TIMEOUT:
		MessageBox(_T("��ⲻ�������ղ�����!\n��ر����������!"), _T("������"), MB_OK);
		m_pWorkThread->EndTask();
		break;

	case WTE_OPEN_ERROR:
		MessageBox(_T("�ܾ�����ϵͳ�ڴ�!\n��ر����������!"), _T("������"), MB_OK);
		m_pWorkThread->EndTask();
		break;

	case WTE_OPENFILE_FAIL:
		MessageBox(_T("�޷���QSV�ļ�!\n��ر����������!"), _T("������"), MB_OK);
		m_pWorkThread->EndTask();
		break;

	case WTE_FIND_FAIL:
		MessageBox(_T("û���ҵ���Ч����!\n��ر����������!"), _T("������"), MB_OK);
		m_pWorkThread->EndTask();
		break;

	case WTE_MALLOC_FAIL:
		MessageBox(_T("ϵͳ�ڴ治��!\n��ر����������!"), _T("������"), MB_OK);
		m_pWorkThread->EndTask();
		break;

	case WTE_CREATE_FAIL:
		MessageBox(_T("�����ļ�ʧ��!\n��ر����������!"), _T("������"), MB_OK);
		m_pWorkThread->EndTask();
		break;

	case WTE_FLV_INVALID:
		MessageBox(_T("����������Ч!\n��ر����������!"), _T("������"), MB_OK);
		m_pWorkThread->EndTask();
		break;

	default:break;
	}
	return 1;
}

//�߳�ֹͣ
LRESULT CQSV2FLVDlg::OnWorkThreadStop(WPARAM wParam, LPARAM lParam)
{
	GetDlgItem(IDC_BTN_ADD)->EnableWindow(1);
	GetDlgItem(IDC_BTN_DEL)->EnableWindow(1);
	GetDlgItem(IDC_BTN_START)->EnableWindow(1);
	GetDlgItem(IDC_BTN_STOP)->EnableWindow(0);
	m_ctrlList.SetItemText(m_nCurIndex, 2, _T("��ֹͣ!"));
	return 1;
}
