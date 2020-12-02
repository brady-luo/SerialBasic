#include "pch.h"
#include "SerialPort.h"

CSerialPort::CSerialPort(void)
{
	m_hComm = NULL;
}

CSerialPort::~CSerialPort(void)
{
	CloseComm();
}

void CSerialPort::StartComm()
{
	m_ThreadComm.SetThreadData((DWORD)this);
	m_ThreadComm.Start();
}


BOOL CSerialPort::OpenComm(CString strComm)
{
	if (NULL == m_hComm) {
		m_hComm = CreateFile(strComm, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED, 0);
	
		if (INVALID_HANDLE_VALUE == m_hComm) {
			int mError = GetLastError();
			m_hComm = NULL;
			AfxMessageBox(_T("串口不存在或已被占用"));
			return FALSE;
		}
		return TRUE;
	}

	return FALSE;
}

BOOL CSerialPort::SetCommState(DWORD dwBaudrate, BYTE byParity, BYTE byByteSize, BYTE byStopBits)
{
	if (NULL == m_hComm) return FALSE;

	DCB dcb;
	BOOL bRet = ::GetCommState(m_hComm, &dcb);
	if (!bRet) {
		if (m_hComm) {
			CloseHandle(m_hComm);
			m_hComm = NULL;
		}
		return FALSE;
	}

	dcb.BaudRate = dwBaudrate;
	dcb.ByteSize = byByteSize;
	dcb.Parity = byParity;
	dcb.StopBits = byStopBits;
	bRet = ::SetCommState(m_hComm, &dcb);
	if (!bRet) {
		if (m_hComm) {
			CloseHandle(m_hComm);
			m_hComm = NULL;
		}
		return FALSE;
	}
	
	return TRUE;
}

BOOL CSerialPort::SetupComm(DWORD dwInqueue, DWORD dwOutqueue)
{
	if (NULL == m_hComm) return FALSE;

	return ::SetupComm(m_hComm, dwInqueue, dwOutqueue);
}

BOOL CSerialPort::PurgeComm(DWORD dwFlags)
{
	if (NULL == m_hComm) return FALSE;

	return ::PurgeComm(m_hComm, dwFlags);
}

BOOL CSerialPort::SetCommMask(DWORD dwEvtMask)
{
	if (NULL == m_hComm) return FALSE;

	return ::SetCommMask(m_hComm, dwEvtMask);
}

BOOL CSerialPort::WriteFile(IN LPCVOID lpBuffer, IN DWORD nNumberOfBytesToWrite, OUT LPDWORD lpNumberOfBytesWritten, IN LPOVERLAPPED lpOverlapped)
{
	if (NULL == m_hComm) return FALSE;

	return ::WriteFile(m_hComm, lpBuffer, nNumberOfBytesToWrite, lpNumberOfBytesWritten, lpOverlapped);
}

BOOL CSerialPort::ReadFile(OUT LPVOID lpBuffer, IN DWORD nNumberOfBytesToRead, OUT LPDWORD lpNumberOfBytesRead, IN LPOVERLAPPED lpOverlapped)
{
	if (NULL == m_hComm) return FALSE;

	return ::ReadFile(m_hComm, lpBuffer, nNumberOfBytesToRead, lpNumberOfBytesRead, lpOverlapped);
}

BOOL CSerialPort::ClearCommError(OUT LPDWORD lpErrors, OUT LPCOMSTAT lpStat)
{
	if (NULL == m_hComm) return FALSE;

	return ::ClearCommError(m_hComm, lpErrors, lpStat);
}

BOOL CSerialPort::GetOverlappedResult(IN LPOVERLAPPED lpoverlapped, OUT LPDWORD lpNumberOfBytesTransferred, IN BOOL bWait)
{
	if (NULL == m_hComm) return FALSE;

	return ::GetOverlappedResult(m_hComm, lpoverlapped, lpNumberOfBytesTransferred, bWait);
}

void CSerialPort::CloseComm()
{
	m_ThreadComm.Stop();

	if (m_hComm) {
		CloseHandle(m_hComm);
		m_hComm = NULL;
	}
}



