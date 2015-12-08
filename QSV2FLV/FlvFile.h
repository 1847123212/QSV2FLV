#pragma once

typedef struct
{
	BYTE	biType;			//Tag����
	DWORD	dwDataSize;		//���ݳ���
	DWORD	dwTimeStamp;	//ʱ���ǰ3�ֽڴ�˸�ʽ�����һ�ֽ�Ϊ���λ
	DWORD	dwStreamID;		//��ID��ʼ��Ϊ0
	BYTE*	pData;
	DWORD	dwTagSize;
	BYTE*	pNextTag;		//��һ��Tag��ַ
	BYTE*	pMemEnd;		//�ڴ������ַ
}FLV_TAG;


class CFlvFile
{
public:
	//����FLV�ļ�
	BOOL Create(LPCTSTR pzFileName);

	//׷������
	void Write(LPCVOID lpData, UINT nLen);

	//׷��Tag
	void WriteTag(FLV_TAG *pTag);

	//ʶ���Ƿ���ȷ��FLV
	BOOL IsVaildFlvMem(LPCVOID lpMem);

	//��ȡ��һ��Tag
	BOOL GetFirstTagFromMem(FLV_TAG* pTag, LPCVOID lpMem, UINT nSize);

	//��ȡ��һ��Tag
	BOOL GetNextTagFromMem(FLV_TAG* pTag);

	//���ڴ��ȡ��ȥMeta��Ϣ������
	BOOL GetNoScriptDataFromMem(LPCVOID lpMem, UINT nMemSize, LPVOID &lpData, UINT *nDataSize);

	//���ڴ��ȡ��ȥ��һ���ؼ�֡������
	BOOL GetNoKeyTagDataFromMem(LPCVOID lpMem, UINT nMemSize, LPVOID &lpData, UINT *nDataSize);

	//�ر�
	void Close();


private:
	//�۵��ֽ�˳��
	void Big2Littel(LPCVOID lpDest, LPVOID lpSrc, UINT Len);


private:
	CFile m_hFile;
};
