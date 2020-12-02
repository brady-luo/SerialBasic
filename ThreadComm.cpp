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
	Sleep(100);
	CMFCSerialBasicDlg* pMFCSerialDlg = (CMFCSerialBasicDlg*)AfxGetApp()->m_pMainWnd;
	if (NULL == pMFCSerialDlg) {
		return;
	}

	CSerialPort* pSerialPort = (CSerialPort*)GetThreadData(); //不太理解
	if (NULL == pSerialPort) return;

	DWORD dwError = 0;
	COMSTAT comStat;
	BOOL bRet = TRUE;
	TCHAR recvTemp[512];
	ZeroMemory(recvTemp, sizeof(recvTemp));

	TCHAR recvBuff[4096];
	ZeroMemory(recvBuff, sizeof(recvBuff));

	DWORD dwRead = 0; //读取的大小
	int nLength = 0;

	pSerialPort->ClearCommError(&dwError, &comStat); //判断缓冲区中是否有数据
	if (comStat.cbInQue > 0)
	{
		OVERLAPPED overlappedRead;
		ZeroMemory(&overlappedRead, sizeof(OVERLAPPED));
		overlappedRead.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

		if (comStat.cbInQue < 512) {
			bRet = pSerialPort->ReadFile(recvTemp, comStat.cbInQue, &dwRead, &overlappedRead);
		}
		else {
			bRet = pSerialPort->ReadFile(recvTemp, 500, &dwRead, &overlappedRead);
		}

		if (comStat.cbInQue >= dwRead) {   //不理解
			memcpy(recvBuff+nLength, recvTemp, dwRead);
			nLength += dwRead;
		}
		if (overlappedRead.hEvent != 0) {
			CloseHandle(overlappedRead.hEvent);
		}		

		if (comStat.cbInQue == dwRead) {   //不理解
			nLength = 0;
			CEdit* pEditRecv = (CEdit*)pMFCSerialDlg->GetDlgItem(IDC_EDIT_RECV);
			if (pEditRecv) {
				CString strRecv;
				pEditRecv->GetWindowText(strRecv);
				strRecv += _T("Recv: ");
				strRecv += recvBuff;
				strRecv += _T("\r\n");
				pEditRecv->SetWindowText(strRecv);
			}
		}

		//不理解
		if (!bRet)
		{
			if (ERROR_IO_PENDING == GetLastError()) {
				while (!bRet)
				{
					bRet = pSerialPort->GetOverlappedResult(NULL, &dwRead, TRUE);
					if (GetLastError() != ERROR_IO_INCOMPLETE) {
						pSerialPort->ClearCommError(&dwError, &comStat);
						break;
					}
				}
			}
		}
	}
}
