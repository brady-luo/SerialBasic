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
	static DWORD ThreadProc(LPVOID pParam);  //����ϵͳ�ص�����

public:
	HANDLE m_hThread;
	bool m_bExit; //�߳��Ƿ��˳�
	DWORD m_dwParam; //�����̵߳Ĳ���
};

