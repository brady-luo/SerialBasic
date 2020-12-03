#include "pch.h"
#include "Thread.h"



CThread::CThread()
{
	m_bExit = false;
	m_dwParam = 0;
	m_hThread = NULL;
}

CThread::~CThread()
{
	if (!m_bExit) {
		Stop();
	}
}

//�����̣߳�����ǰ�߳̾�� ���� m_hThread
void CThread::Start()
{
	DWORD dwThreadID = 0;
	HANDLE hThread = ::CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadProc, this, 0, &dwThreadID);
	ASSERT(hThread);
	m_hThread = hThread;
	m_bExit = false; //��δ�ʱ����Ҫִ�и���
}

//�ر��߳�
void CThread::Stop()
{
	if (m_hThread) {
		m_bExit = true;
		::WaitForSingleObject(m_hThread, INFINITE); //��Ҫ�ȴ��߳̽������ܹر�m_HThread
		::CloseHandle(m_hThread);
		m_hThread = NULL;
	}
}


DWORD CThread::ThreadProc(LPVOID pParam)
{
	CThread* pThis = (CThread*)pParam;
	ASSERT(pThis);

	while (!pThis ->m_bExit)
	{
		pThis->run();
	}
	return TRUE;
}


void CThread::SetThreadData(DWORD dwParam)
{
	if (m_dwParam != dwParam) {
		m_dwParam = dwParam;
	}
}

DWORD CThread::GetThreadData()
{
	return m_dwParam;
}

void CThread::run()
{
	Sleep(100); //���100ms ����ռ�ù�����Դ
}

