#include "pch.h"
#include "ThreadComm.h"
#include "MFCSerialBasic.h"
#include "MFCSerialBasicDlg.h"

CThreadComm::CThreadComm()
{
}

CThreadComm::~CThreadComm()
{
}

void CThreadComm::run()
{
	Sleep(100); //���100ms ����ռ�ù�����Դ

	CMFCSerialBasicDlg* pMFCSerialDlg = (CMFCSerialBasicDlg*)AfxGetApp()->m_pMainWnd;  //��ȡdialogue���thisָ��
	if (NULL == pMFCSerialDlg) {
		return;
	}

	CSerialPort* pSerialPort = (CSerialPort*)GetThreadData(); //��ȡ�������thisָ��
	if (NULL == pSerialPort) return;

	BOOL bRet = TRUE;
	DWORD dwError = 0;  //���մ���
	COMSTAT comStat;   //����������
	
	TCHAR recvTemp[512]; //һ�ζ�ȡ����ʱ�ռ�
	ZeroMemory(recvTemp, sizeof(recvTemp));
	TCHAR recvBuff[4096]; //���յ������ݿռ�
	ZeroMemory(recvBuff, sizeof(recvBuff));

	DWORD dwRead = 0; //ʵ�ʶ�ȡ���ֽ���
	int nLength = 0;

	pSerialPort->ClearCommError(&dwError, &comStat); //�жϻ��������Ƿ�������
	if (comStat.cbInQue > 0)
	{
		OVERLAPPED overlappedRead;   //overlapped�ṹ�÷�
		ZeroMemory(&overlappedRead, sizeof(OVERLAPPED));
		overlappedRead.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

		if (comStat.cbInQue < 512) {  //comStat.cbInQueҪ��ȡ���ֽ���
			bRet = pSerialPort->ReadFile(recvTemp, comStat.cbInQue, &dwRead, &overlappedRead);  //���Ҫ��ȡ���ֽ���С��512����ȫ����ȡ
		}
		else {
			bRet = pSerialPort->ReadFile(recvTemp, 500, &dwRead, &overlappedRead);   //���Ҫ��ȡ���ֽ�������512�����ȶ�ȡ500
		}

		
		
		if (!bRet)
		{
			if (ERROR_IO_PENDING == GetLastError()) {  //���ReadFile�����ˣ��ȴ�����ִ����
				while (!bRet)
				{
					bRet = pSerialPort->GetOverlappedResult(&overlappedRead, &dwRead, TRUE); //������ΪTRUE���������֮ǰ�����з���
					if (GetLastError() != ERROR_IO_INCOMPLETE) {
						pSerialPort->ClearCommError(&dwError, &comStat);
						break;
					}
				}
			}
		}


		if (comStat.cbInQue >= dwRead) {
			memcpy(recvBuff + nLength, recvTemp, dwRead);  //��һ�ζ�ȡ�����ݿ�����recvBuff
			nLength += dwRead;
		}


		if (comStat.cbInQue == dwRead) {   //��ʵ�ʽ��յ������ݺ�Ҫ���յ��������ʱ��˵����������
			nLength = 0;
			CEdit* pEditRecv = (CEdit*)pMFCSerialDlg->GetDlgItem(IDC_EDIT_RECV);
			if (pEditRecv) {
				CString strRecv;
				pEditRecv->GetWindowText(strRecv);
				strRecv += _T("Recv: ");
				strRecv += recvBuff;
				strRecv += _T("\r\n");
				pEditRecv->SetWindowText(strRecv); //��SetSel(-1); ReplaceSel �����
			}
		}

		if (overlappedRead.hEvent != 0) {
			CloseHandle(overlappedRead.hEvent);  //�ر�overlappedRead�ṹ�¼�
		}
	}
}
