#include "StdAfx.h"
#include "FlvFile.h"

static BYTE g_biFlvHead[]={0x46,0x4C,0x56,0x01,0x05,0x00,0x00,0x00,0x09,0x00,0x00,0x00,0x00};

typedef struct
{
	BYTE biType;			//Tag����
	BYTE biDataSize[3];		//���ݳ���
	BYTE biTimeStamp[3];	//ʱ���3�ֽڴ�˸�ʽ
	BYTE biTimeHiByte;		//ʱ������ֽ�
	BYTE biStreamID[3];		//��ID��ʼ��Ϊ0
}TAG_DATA;

//����FLV�ļ�
BOOL CFlvFile::Create(LPCTSTR pzFileName)
{
	if (m_hFile.m_hFile != INVALID_HANDLE_VALUE)
	{
		m_hFile.Close();
		OutputDebugString(_T("Create Not Closed!\n"));
	}
	BOOL bRet =  m_hFile.Open(pzFileName, CFile::modeCreate|CFile::modeReadWrite);
	if (!bRet)
		return FALSE;

	m_hFile.SeekToBegin();
	m_hFile.Write(g_biFlvHead, sizeof(g_biFlvHead));
	OutputDebugString(_T("Create FLV OK:"));
	OutputDebugString(pzFileName);
	return TRUE;
}

//׷������
void CFlvFile::Write(LPCVOID lpData, UINT nLen)
{
	m_hFile.SeekToEnd();
	m_hFile.Write(lpData, nLen);
}


void CFlvFile::WriteTag(FLV_TAG *pTag)
{
	TAG_DATA tagData;
	DWORD    dwTagSize = 0;
	ZeroMemory(&tagData, sizeof(TAG_DATA));
	tagData.biType = pTag->biType;
	Big2Littel(tagData.biDataSize, &pTag->dwDataSize, 3);
	Big2Littel(tagData.biTimeStamp, &pTag->dwTimeStamp, 3);
	tagData.biTimeHiByte = (BYTE)((pTag->dwTimeStamp >> 24)&0xFF);
	Big2Littel(&dwTagSize, &pTag->dwTagSize, 4);

	m_hFile.SeekToEnd();
	m_hFile.Write(&tagData, sizeof(TAG_DATA));
	m_hFile.Write(pTag->pData, pTag->dwDataSize);
	m_hFile.Write(&dwTagSize, 4);
}

//ʶ���Ƿ���ȷ��FLV
BOOL CFlvFile::IsVaildFlvMem(LPCVOID lpMem)
{
	int nCmp = memcmp(g_biFlvHead, lpMem, sizeof(g_biFlvHead));
	if (nCmp == 0)
		return TRUE;
	return FALSE;
}


//��ȡ��һ��Tag
BOOL CFlvFile::GetFirstTagFromMem(FLV_TAG* pTag, LPCVOID lpMem, UINT nMemSize)
{
	TAG_DATA* pTagData = NULL;
	pTagData = (TAG_DATA*)((BYTE*)lpMem+13);
	memset(pTag, 0, sizeof(FLV_TAG));

	pTag->biType = pTagData->biType;	//����
	if ((pTag->biType != 0x08)&&(pTag->biType != 0x09)&&(pTag->biType != 0x12))
		return FALSE;

	Big2Littel(&pTag->dwDataSize, pTagData->biDataSize, 3);	//���ݳ���
	Big2Littel(&pTag->dwTimeStamp, pTagData->biTimeStamp, 3);//ʱ��
	pTag->dwTimeStamp |= (pTagData->biTimeHiByte<<24);
	Big2Littel(&pTag->dwStreamID, pTagData->biStreamID, 3);	//��ID
	if (pTag->dwStreamID != 0)
		return FALSE;
	pTag->pData = ((BYTE*)pTagData + sizeof(TAG_DATA));		//����
	pTag->dwTagSize= pTag->dwDataSize + 11;					//Tag�ܳ���
	pTag->pNextTag = ((BYTE*)pTagData + pTag->dwTagSize + 4);	//��һ��Tag
	pTag->pMemEnd = (BYTE*)lpMem + nMemSize;

	if (pTag->pNextTag >= pTag->pMemEnd)	//�ڴ泬��
		return FALSE;

	//��֤Tag
	DWORD dwTagSize = 0;
	Big2Littel(&dwTagSize, (pTag->pNextTag-4), 4);
	if (dwTagSize != pTag->dwTagSize)
		return FALSE;

	return TRUE;
}

BOOL CFlvFile::GetNextTagFromMem(FLV_TAG* pTag)
{
	TAG_DATA* pTagData = NULL;
	pTagData = (TAG_DATA*)(pTag->pNextTag);

	if (pTag->pNextTag >= pTag->pMemEnd)	//�ڴ泬��
		return FALSE;

	pTag->biType = pTagData->biType;	//����
	if ((pTag->biType != 0x08)&&(pTag->biType != 0x09)&&(pTag->biType != 0x12))
		return FALSE;

	pTag->dwDataSize = 0;
	Big2Littel(&pTag->dwDataSize, pTagData->biDataSize, 3);	//���ݳ���

	pTag->dwTimeStamp = 0;
	Big2Littel(&pTag->dwTimeStamp, pTagData->biTimeStamp, 3);//ʱ��
	pTag->dwTimeStamp |= (pTagData->biTimeHiByte<<24);

	pTag->dwStreamID = 0;
	Big2Littel(&pTag->dwStreamID, pTagData->biStreamID, 3);	//��ID
	if (pTag->dwStreamID != 0)
		return FALSE;

	pTag->pData = ((BYTE*)pTagData + sizeof(TAG_DATA));		//����
	pTag->dwTagSize= pTag->dwDataSize + 11;					//Tag�ܳ���
	pTag->pNextTag = ((BYTE*)pTagData + pTag->dwTagSize + 4);	//��һ��Tag

	//��֤Tag
	DWORD dwTagSize = 0;
	Big2Littel(&dwTagSize, (pTag->pNextTag-4), 4);
	if (dwTagSize != pTag->dwTagSize)
		return FALSE;

	return TRUE;
}

//���ڴ��ȡ����Meta��Ϣ������
//Tag���� Type+Size+Time+Stream+TagSize=1+3+4+3+4=15
//ͷ�� 13
BOOL CFlvFile::GetNoScriptDataFromMem(LPCVOID lpMem, UINT nMemSize, LPVOID &lpData, UINT *nDataSize)
{
	BOOL	bRet;
	FLV_TAG flvTag;
	bRet = GetFirstTagFromMem(&flvTag, lpMem, nMemSize);
	if (!bRet)
		return FALSE;

	lpData = flvTag.pNextTag;
	*nDataSize = (UINT)(flvTag.pMemEnd - flvTag.pNextTag);
	return TRUE;
}

//���ڴ��ȡ��ȥ��һ���ؼ�֡������
//ʵ�ʾ�������3֡
BOOL CFlvFile::GetNoKeyTagDataFromMem(LPCVOID lpMem, UINT nMemSize, LPVOID &lpData, UINT *nDataSize)
{
	BOOL	bRet;
	FLV_TAG flvTag;
	bRet = GetFirstTagFromMem(&flvTag, lpMem, nMemSize);	//����0x12
	if (!bRet)
		return FALSE;

	bRet = GetNextTagFromMem(&flvTag);	//����0x09
	if (!bRet)
		return FALSE;
	bRet = GetNextTagFromMem(&flvTag);	//����0x08
	if (!bRet)
		return FALSE;
	
	lpData = flvTag.pNextTag;
	*nDataSize =(UINT)(flvTag.pMemEnd - flvTag.pNextTag);
	return TRUE;
}

//�ر�
void CFlvFile::Close()
{
	m_hFile.Close();
	OutputDebugString(_T("FLV file Closed!\n"));
}


void CFlvFile::Big2Littel(LPCVOID lpDest, LPVOID lpSrc, UINT Len)
{
	UINT i;
	for(i=0; i<Len; i++)
	{
		((BYTE*)lpDest)[i] = ((BYTE*)lpSrc)[Len-i-1];
	}
}
