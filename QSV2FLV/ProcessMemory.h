#pragma once

class CProcessMemory
{
public:
	//�򿪽����ڴ�
	BOOL    Open(INT nPID);
	BOOL    Open(LPCTSTR pzProcessName);

	//����,���ƥ��256�ֽڳ���
	LPCVOID Find(LPVOID lpMatchBuffer, BYTE biMatchSize);

	//д��
	DWORD   Write(LPVOID lpBaseAddress,  LPVOID lpBuffer, DWORD nSize);

	//��ȡ
	DWORD   Read(LPCVOID  lpBaseAddress,  LPVOID lpBuffer, DWORD nSize);

	//�ر�
	void    Close();

private:
	BOOL    SetPrivilege(HANDLE hToken, LPCTSTR lpszStr, BOOL bEnable);
	INT		GetProcessID(LPCTSTR pzProcessName);

private:
	HANDLE	m_hProc;
};
