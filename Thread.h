#pragma once
class CThread
{
public:
	CThread();
	~CThread();

public:
	void Start();
	void Stop();

public:
	virtual void SetThreadData(DWORD dwParam);
	virtual DWORD GetThreadData();

public:
	virtual void run();


public:
	static DWORD ThreadProc(LPVOID pParam);  //操作系统回调函数

public:
	HANDLE m_hThread;
	bool m_bExit; //线程是否退出
	DWORD m_dwParam; //传给线程的参数
};

