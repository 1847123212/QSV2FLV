#pragma once

class CQiyiFile
{
public:
	BOOL Open(LPCTSTR pzFileName);
	void GetFileTitle(CString& szFileTitle);
	BOOL IsQiYiFile();
	INT  GetSectionCount();

	//��ȡ�ֶ����ݣ�����ǰ0x400�ļ�������
	BOOL ReadSection(DWORD dwBase, BYTE *pData, UINT nLen);
	void Close();

private:
	CFile m_hFile;
};
