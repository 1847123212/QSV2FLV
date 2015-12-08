// AboutDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "QSV2FLV.h"
#include "AboutDlg.h"


// CAboutDlg �Ի���

IMPLEMENT_DYNAMIC(CAboutDlg, CDialog)

CAboutDlg::CAboutDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAboutDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CAboutDlg::~CAboutDlg()
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &CAboutDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CAboutDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CAboutDlg ��Ϣ�������
BOOL CAboutDlg::OnInitDialog()
{
	CString szAbout(_T(""));
	CDialog::OnInitDialog();
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��
	szAbout += _T("������ƣ�QSV2FLV\n");
	szAbout += _T("����汾��");
	szAbout += STR_VERSION;
	szAbout += _T("\n�������ڣ�");
	szAbout += STR_DATE;
	szAbout += _T("\n");
	szAbout += _T("�������䣺446252221@qq.com\n");
	szAbout += _T("���Եİ����հ汾��");
	szAbout += STR_QIYI_VER;
	szAbout += _T("\n");
	SetDlgItemText(IDC_TEXT_ABOUT, szAbout);


	CString szInfo(_T(""));
	szInfo += _T("���ڰ����ո��±Ƚ�Ƶ������������ʱ���ܻ���Ϊ���¶���Ч��\n");
	szInfo += _T("��������������߶�������ã������ʹ����֧���������ҡ�");
	SetDlgItemText(IDC_TEXT_PS, szInfo);

	SetDlgItemText(IDC_BUTTON1, _T("����"));
	return TRUE;
}

void CAboutDlg::OnBnClickedButton1()
{
	//
}

void CAboutDlg::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString szUrl;
	szUrl = _T("http://pan.baidu.com/share/home?uk=1526776463");
	::ShellExecute(NULL, _T("open"), szUrl, NULL, NULL, SW_SHOW);
}
