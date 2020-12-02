#pragma once
#include "ThreadComm.h"

class CSerialPort
{
public:
	CSerialPort(void);
	~CSerialPort(void);

public:
	BOOL OpenComm(CString strComm);
	BOOL SetCommState(DWORD dwBaudrate, BYTE byParity, BYTE byByteSize, BYTE byStopBits);
	BOOL SetupComm(DWORD dwInqueue, DWORD dwOutqueue);  //�������������������С�����ֽ�Ϊ��λ
	BOOL PurgeComm(DWORD dwFlags);  //��ջ�����
	BOOL SetCommMask(DWORD dwEvtMask);  //���ô���ͨ���¼�
	BOOL WriteFile(IN LPCVOID lpBuffer, IN DWORD nNumberOfBytesToWrite, OUT LPDWORD lpNumberOfBytesWritten, IN LPOVERLAPPED lpOverlapped);
	BOOL ReadFile(OUT LPVOID lpBuffer, IN DWORD nNumberOfBytesToRead, OUT LPDWORD lpNumberOfBytesRead, IN LPOVERLAPPED lpOverlapped);
	BOOL ClearCommError(OUT LPDWORD lpErrors, OUT LPCOMSTAT lpStat);
	BOOL GetOverlappedResult(IN LPOVERLAPPED lpoverlapped, OUT LPDWORD lpNumberOfBytesTransferred, IN BOOL bWait);
	
public:
	void StartComm();  //����һ���߳�
	void CloseComm();  //�ر��̣߳��رմ���

public:
	HANDLE m_hComm;
	CThreadComm m_ThreadComm;  //ʵ����һ�������߳��࣬�̳��߳���
};

