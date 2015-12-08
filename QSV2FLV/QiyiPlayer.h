#pragma once

#define		QSV_INFO_SIZE	0x50		//�������ֳ���
#define		QSV_ENC_SIZE	0x400		//���ܳ���

//�����������ڴ��в���
//0x50 + 0x400
//0x38 Base
//0x40 Size
typedef struct
{
	BYTE	Reserved1[0x38];
	DWORD	dwOffset;				//��QSV�ļ��е�ƫ�Ƶ�ַ
	BYTE    Reserved2[4];
	DWORD	dwSize;					//�ֶ��ļ�����
	BYTE	Reserved3[0x0C];
	BYTE	biFLV[QSV_ENC_SIZE];	//���ܺ��FLVͷ��
}QIYI_INFO;					//һ��0x450�ֽ�



class CQiyiPlayer
{
public:
	//���ڲ���QSV�ļ�������ⲥ�����Ƿ�ʼ����
	//����1:���ֲ�����
	//����0:û�з��ֲ�����
	BOOL Play(LPCTSTR pzFileName);
	void Close();

	INT  GetPid(){return m_nPidPlayer;}

private:
	BOOL WaitForPlay(INT nTimeout);

private:
	INT  m_nPidPlayer;
	HWND m_hWndClient;
	HWND m_hWndPlayer;
};
