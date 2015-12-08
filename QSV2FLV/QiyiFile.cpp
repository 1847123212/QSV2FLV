#include "StdAfx.h"
#include "QiyiFile.h"

BOOL CQiyiFile::Open(LPCTSTR pzFileName)
{
	if (m_hFile.m_hFile != INVALID_HANDLE_VALUE)
	{
		m_hFile.Close();
	}
	return m_hFile.Open(pzFileName, CFile::modeRead | CFile::shareDenyNone);
}

void CQiyiFile::GetFileTitle(CString& szFileTitle)
{
	szFileTitle = m_hFile.GetFileName();
}

//�Ƿ���ЧQSV�ļ�
BOOL CQiyiFile::IsQiYiFile()
{
	BOOL bRet;
	BYTE biHead[20]= "QIYI VIDEO";
	BYTE biRead[20];

	m_hFile.SeekToBegin();
	bRet = m_hFile.Read(biRead, 10);	//ǰ10�ֽ�
	if(bRet == FALSE)
		return FALSE;

	if(memcmp(biHead, biRead, 10) != 0)
		return FALSE;

	return TRUE;
}

//��ȡ�ֶ�����
INT  CQiyiFile::GetSectionCount()
{
	INT  nCount = 0;
	m_hFile.Seek(0x56, CFile::begin);	//0x56���ֵ�Ƿ��ȷ��?
	m_hFile.Read(&nCount, sizeof(nCount));
	return nCount;
}


BOOL CQiyiFile::ReadSection(DWORD dwBase, BYTE *pData, UINT nLen)
{
	m_hFile.Seek(dwBase, CFile::begin);
	return m_hFile.Read(pData, nLen);
}

void CQiyiFile::Close()
{
	m_hFile.Close();
}
