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
	Sleep(100); //间隔100ms 避免占用过多资源

	CMFCSerialBasicDlg* pMFCSerialDlg = (CMFCSerialBasicDlg*)AfxGetApp()->m_pMainWnd;  //获取dialogue类的this指针
	if (NULL == pMFCSerialDlg) {
		return;
	}

	CSerialPort* pSerialPort = (CSerialPort*)GetThreadData(); //获取串口类的this指针
	if (NULL == pSerialPort) return;

	BOOL bRet = TRUE;
	DWORD dwError = 0;  //接收错误
	COMSTAT comStat;   //接收数据量
	
	TCHAR recvTemp[512]; //一次读取的临时空间
	ZeroMemory(recvTemp, sizeof(recvTemp));
	TCHAR recvBuff[4096]; //接收到的数据空间
	ZeroMemory(recvBuff, sizeof(recvBuff));

	DWORD dwRead = 0; //实际读取的字节数
	int nLength = 0;

	pSerialPort->ClearCommError(&dwError, &comStat); //判断缓冲区中是否有数据
	if (comStat.cbInQue > 0)
	{
		OVERLAPPED overlappedRead;   //overlapped结构用法
		ZeroMemory(&overlappedRead, sizeof(OVERLAPPED));
		overlappedRead.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

		if (comStat.cbInQue < 512) {  //comStat.cbInQue要读取的字节数
			bRet = pSerialPort->ReadFile(recvTemp, comStat.cbInQue, &dwRead, &overlappedRead);  //如果要读取的字节数小于512，就全部读取
		}
		else {
			bRet = pSerialPort->ReadFile(recvTemp, 500, &dwRead, &overlappedRead);   //如果要读取的字节数大于512，就先读取500
		}

		
		
		if (!bRet)
		{
			if (ERROR_IO_PENDING == GetLastError()) {  //如果ReadFile挂起了，等待操作执行完
				while (!bRet)
				{
					bRet = pSerialPort->GetOverlappedResult(&overlappedRead, &dwRead, TRUE); //最后参数为TRUE，操作完成之前不会有返回
					if (GetLastError() != ERROR_IO_INCOMPLETE) {
						pSerialPort->ClearCommError(&dwError, &comStat);
						break;
					}
				}
			}
		}


		if (comStat.cbInQue >= dwRead) {
			memcpy(recvBuff + nLength, recvTemp, dwRead);  //将一次读取的数据拷贝给recvBuff
			nLength += dwRead;
		}


		if (comStat.cbInQue == dwRead) {   //当实际接收到的数据和要接收的数据相等时，说明接收完了
			nLength = 0;
			CEdit* pEditRecv = (CEdit*)pMFCSerialDlg->GetDlgItem(IDC_EDIT_RECV);
			if (pEditRecv) {
				CString strRecv;
				pEditRecv->GetWindowText(strRecv);
				strRecv += _T("Recv: ");
				strRecv += recvBuff;
				strRecv += _T("\r\n");
				pEditRecv->SetWindowText(strRecv); //用SetSel(-1); ReplaceSel 会更好
			}
		}

		if (overlappedRead.hEvent != 0) {
			CloseHandle(overlappedRead.hEvent);  //关闭overlappedRead结构事件
		}
	}
}
