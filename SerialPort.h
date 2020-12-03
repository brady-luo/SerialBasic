#pragma once
#include "ThreadComm.h"

class CSerialPort
{
public:
	CSerialPort(void);
	~CSerialPort(void);

public:
	BOOL OpenComm(CString strComm);  //创建串口
	BOOL SetCommState(DWORD dwBaudrate, BYTE byParity, BYTE byByteSize, BYTE byStopBits);
	BOOL SetupComm(DWORD dwInqueue, DWORD dwOutqueue);  //设置输入、输出缓存区大小，以字节为单位
	BOOL PurgeComm(DWORD dwFlags);  //清空缓冲区
	BOOL SetCommMask(DWORD dwEvtMask);  //设置串口通信事件，过滤掉不想执行的事件类型
	BOOL WriteFile(IN LPCVOID lpBuffer, IN DWORD nNumberOfBytesToWrite, OUT LPDWORD lpNumberOfBytesWritten, IN LPOVERLAPPED lpOverlapped);
	BOOL ReadFile(OUT LPVOID lpBuffer, IN DWORD nNumberOfBytesToRead, OUT LPDWORD lpNumberOfBytesRead, IN LPOVERLAPPED lpOverlapped);
	BOOL ClearCommError(OUT LPDWORD lpErrors, OUT LPCOMSTAT lpStat);  //判断缓冲区中是否有数据(comStat.cbInQue(lpStat)>0)、是否有错误(comStat.cbInQue(lpStat)<0)
	BOOL GetOverlappedResult(IN LPOVERLAPPED lpoverlapped, OUT LPDWORD lpNumberOfBytesTransferred, IN BOOL bWait); //获取overlapped操作结果
	
public:
	void StartComm();  //创建一个线程
	void CloseComm();  //关闭线程，关闭串口

public:
	HANDLE m_hComm;
	CThreadComm m_ThreadComm;  //实例化一个串口线程类，继承线程类
};

