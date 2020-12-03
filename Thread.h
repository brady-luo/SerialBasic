/*
//�̻߳���
//�̳С�����run(),��Ҫִ�е������ڴ�ʵ�֣�
//�ȵ���SetThreadData(DWORD dwParam)������thisָ��;
//�ٵ���start()�����̡߳�ִ��ThreadProc()������ִ��run()����
*/


#pragma once
class CThread
{
public:
	CThread();
	~CThread();

public:
	void Start(); //�����̣߳�����ǰ�߳̾�� ���� m_hThread
	void Stop(); //�ر��߳�

public:
	virtual void SetThreadData(DWORD dwParam); //���ڴ�����һ��������thisָ��
	virtual DWORD GetThreadData(); //��ȡdwParam������������һ��������thisָ��

public:
	virtual void run();  //�߳�ִ�еĺ���


public:
	static DWORD ThreadProc(LPVOID pParam);  //ΪɶҪд�ɾ�̬����

public:
	HANDLE m_hThread; //�߳̾��
	bool m_bExit; //�߳��Ƿ��˳�
	DWORD m_dwParam; //�����̵߳Ĳ���,�ŵ���������thisָ�룬�����ָ�� ��run() ������ķ���
};

