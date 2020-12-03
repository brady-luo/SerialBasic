/*
//线程基类
//继承、重载run(),将要执行的内容在此实现；
//先调用SetThreadData(DWORD dwParam)传进来this指针;
//再调用start()创建线程、执行ThreadProc()、进而执行run()函数
*/


#pragma once
class CThread
{
public:
	CThread();
	~CThread();

public:
	void Start(); //创建线程，将当前线程句柄 传给 m_hThread
	void Stop(); //关闭线程

public:
	virtual void SetThreadData(DWORD dwParam); //用于传进来一个类对象的this指针
	virtual DWORD GetThreadData(); //获取dwParam，即传进来的一个类对象的this指针

public:
	virtual void run();  //线程执行的函数


public:
	static DWORD ThreadProc(LPVOID pParam);  //为啥要写成静态函数

public:
	HANDLE m_hThread; //线程句柄
	bool m_bExit; //线程是否退出
	DWORD m_dwParam; //传给线程的参数,放的是类对象的this指针，用这个指针 在run() 调用类的方法
};

