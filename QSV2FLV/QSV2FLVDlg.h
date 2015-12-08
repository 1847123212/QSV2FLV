// QSV2FLVDlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"
#include "WorkThread.h"


// CQSV2FLVDlg �Ի���
class CQSV2FLVDlg : public CDialog
{
// ����
public:
	CQSV2FLVDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_QSV2FLV_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	virtual void OnOK(){}
	//virtual void OnCancel();
	DECLARE_MESSAGE_MAP()

private:
	CBitmap		m_bmpFold;
	INT			m_nFileCount;	//
	INT			m_nCurIndex;	//��ǰ������ļ�

	CWorkThread*	m_pWorkThread;

public:
	CListCtrl	m_ctrlList;
	CString		m_szPath;
	afx_msg void OnBnClickedBtnAdd();
	afx_msg void OnBnClickedBtnDel();
	afx_msg void OnBnClickedBtnStart();
	afx_msg void OnBnClickedBtnStop();
	afx_msg void OnBnClickedBtnAbout();
	afx_msg void OnBnClickedBtnPath();
	afx_msg void OnBnClickedBtnOpenpath();
	afx_msg void OnTimer(UINT_PTR nIDEvent);

	afx_msg LRESULT OnWorkThreadStart(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnWorkThreadProc(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnWorkThreadResult(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnWorkThreadStop(WPARAM wParam, LPARAM lParam);
};
