
// MFCSerialBasicDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "MFCSerialBasic.h"
#include "MFCSerialBasicDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCSerialBasicDlg 对话框



CMFCSerialBasicDlg::CMFCSerialBasicDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCSERIALBASIC_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCSerialBasicDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCSerialBasicDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_OPENCOMM, &CMFCSerialBasicDlg::OnBnClickedBtnOpencomm)
	ON_BN_CLICKED(IDC_BTN_SEND, &CMFCSerialBasicDlg::OnBnClickedBtnSend)
END_MESSAGE_MAP()


// CMFCSerialBasicDlg 消息处理程序

BOOL CMFCSerialBasicDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	InitComboBox();

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}


void CMFCSerialBasicDlg::InitComboBox()
{
	//初始化串口列表
	CComboBox* pComboComm = (CComboBox*)GetDlgItem(IDC_COMBO_COM);
	ASSERT(pComboComm);
	for (int i = 1; i < 10; i++) {
		CString strComm;
		strComm.Format(_T("COM%d"), i);
		pComboComm->AddString(strComm);
	}
	pComboComm->SetCurSel(0);

	//初始化波特率列表
	CComboBox* pComboBaudrate = (CComboBox*)GetDlgItem(IDC_COMBO_BAUDRATE);
	ASSERT(pComboBaudrate);
	pComboBaudrate->SetItemData(pComboBaudrate->AddString(_T("300")), 300);
	pComboBaudrate->SetItemData(pComboBaudrate->AddString(_T("600")), 600);
	pComboBaudrate->SetItemData(pComboBaudrate->AddString(_T("1200")), 1200);
	pComboBaudrate->SetItemData(pComboBaudrate->AddString(_T("2400")), 2400);
	pComboBaudrate->SetItemData(pComboBaudrate->AddString(_T("4800")), 4800);
	pComboBaudrate->SetItemData(pComboBaudrate->AddString(_T("9600")), 9600);
	pComboBaudrate->SetItemData(pComboBaudrate->AddString(_T("19200")), 19200);
	pComboBaudrate->SetItemData(pComboBaudrate->AddString(_T("38400")), 38400);
	pComboBaudrate->SetItemData(pComboBaudrate->AddString(_T("48000")), 48000);
	pComboBaudrate->SetItemData(pComboBaudrate->AddString(_T("56000")), 56000);
	pComboBaudrate->SetItemData(pComboBaudrate->AddString(_T("57600")), 57600);
	pComboBaudrate->SetItemData(pComboBaudrate->AddString(_T("115200")), 115200);
	pComboBaudrate->SetCurSel(5);

	//初始化校验位列表
	CComboBox* pComboCheckBit = (CComboBox*)GetDlgItem(IDC_COMBO_CHECKBIT);
	ASSERT(pComboCheckBit);
	pComboCheckBit->SetItemData(pComboCheckBit->AddString(_T("None")), NOPARITY);
	pComboCheckBit->SetItemData(pComboCheckBit->AddString(_T("ODD")), ODDPARITY);
	pComboCheckBit->SetItemData(pComboCheckBit->AddString(_T("EVEN")), EVENPARITY);
	pComboCheckBit->SetCurSel(0);

	//初始化数据位列表
	CComboBox* pComboDataBit = (CComboBox*)GetDlgItem(IDC_COMBO_DATABIT);
	ASSERT(pComboDataBit);
	pComboDataBit->SetItemData(pComboDataBit->AddString(_T("6")), 6);
	pComboDataBit->SetItemData(pComboDataBit->AddString(_T("7")), 7);
	pComboDataBit->SetItemData(pComboDataBit->AddString(_T("8")), 8);
	pComboDataBit->SetCurSel(2);

	//初始化停止位列表
	CComboBox* pComboStopBit = (CComboBox*)GetDlgItem(IDC_COMBO_STOPBIT);
	ASSERT(pComboStopBit);
	pComboStopBit->SetItemData(pComboStopBit->AddString(_T("1")), ONESTOPBIT);
	pComboStopBit->SetItemData(pComboStopBit->AddString(_T("2")), TWOSTOPBITS);
	pComboStopBit->SetCurSel(0);

}


void CMFCSerialBasicDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMFCSerialBasicDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMFCSerialBasicDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCSerialBasicDlg::OnBnClickedBtnOpencomm()
{
	static BOOL bIsOpen = FALSE;
	CButton* pBtnOpenComm = (CButton*)GetDlgItem(IDC_BTN_OPENCOMM);
	ASSERT(pBtnOpenComm);

	CComboBox* pComboBoxComm = (CComboBox*)GetDlgItem(IDC_COMBO_COM);
	ASSERT(pComboBoxComm);
	int nSel = pComboBoxComm->GetCurSel();
	CString strComm;
	pComboBoxComm->GetLBText(nSel, strComm);

	CComboBox* pComboBoxBaudrate = (CComboBox*)GetDlgItem(IDC_COMBO_BAUDRATE);
	ASSERT(pComboBoxBaudrate);
	nSel = pComboBoxBaudrate->GetCurSel();
	DWORD dwBaudrate = (DWORD)pComboBoxBaudrate->GetItemData(nSel);

	CComboBox* pComboBoxCheckBit = (CComboBox*)GetDlgItem(IDC_COMBO_CHECKBIT);
	ASSERT(pComboBoxCheckBit);
	nSel = pComboBoxCheckBit->GetCurSel();
	BYTE byCheckBit = (BYTE)pComboBoxCheckBit->GetItemData(nSel);

	CComboBox* pComboBoxDataBit = (CComboBox*)GetDlgItem(IDC_COMBO_DATABIT);
	ASSERT(pComboBoxDataBit);
	nSel = pComboBoxDataBit->GetCurSel();
	BYTE byDataBit = (BYTE)pComboBoxDataBit->GetItemData(nSel);

	CComboBox* pComboBoxStopBit = (CComboBox*)GetDlgItem(IDC_COMBO_STOPBIT);
	ASSERT(pComboBoxStopBit);
	nSel = pComboBoxStopBit->GetCurSel();
	BYTE byStopBit = (BYTE)pComboBoxStopBit->GetItemData(nSel);

	if (!bIsOpen) 
	{
		bIsOpen = gSerialPort.OpenComm(strComm);
		if (bIsOpen) 
		{
			BOOL bRet = gSerialPort.SetCommState(dwBaudrate, byCheckBit, byDataBit, byStopBit);
			if (!bRet) {
				gSerialPort.CloseComm();
				AfxMessageBox(_T("设置串口属性失败！"));
				return;
			}
			
			bRet = gSerialPort.SetupComm(1024, 1024);
			if (!bRet) {
				gSerialPort.CloseComm();
				AfxMessageBox(_T("设置串口输入输出缓冲区大小失败！"));
				return;
			}

			bRet = gSerialPort.PurgeComm(PURGE_RXABORT | PURGE_RXCLEAR | PURGE_TXABORT | PURGE_TXCLEAR);
			if (!bRet) {
				gSerialPort.CloseComm();
				AfxMessageBox(_T("无法清除串口的错误状态！"));
				return;
			}

			bRet = gSerialPort.SetCommMask(EV_RXCHAR);
			if (!bRet) {
				gSerialPort.CloseComm();
				AfxMessageBox(_T("设置串口事件出错！"));
				return;
			}

			gSerialPort.StartComm(); //创建一个线程

			pBtnOpenComm->SetWindowTextW(_T("关闭串口"));
		}
		else
		{
			pBtnOpenComm->SetWindowTextW(_T("打开串口"));
		}
	}
	else
	{
		gSerialPort.CloseComm();
		bIsOpen = FALSE;
		pBtnOpenComm->SetWindowTextW(_T("打开串口"));
	}
}


void CMFCSerialBasicDlg::OnBnClickedBtnSend()
{
	if (NULL == gSerialPort.m_hComm) {
		AfxMessageBox(_T("请打开串口后发送数据！"));
		return;
	}
	CEdit* pEditSend = (CEdit*)GetDlgItem(IDC_EDIT_SEND);
	ASSERT(pEditSend);
	CEdit* pEditRecv = (CEdit*)GetDlgItem(IDC_EDIT_RECV);
	ASSERT(pEditRecv);

	CString strSend;
	CString strRecv;
	pEditSend->GetWindowTextW(strSend);
	strSend = strSend.Trim(); //去除空格
	if (strSend.IsEmpty()) {
		//AfxMessageBox(_T("不能发送空数据！"));
		return;
	}

	OVERLAPPED overlappedWrite;
	ZeroMemory(&overlappedWrite, sizeof(OVERLAPPED));
	overlappedWrite.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

	int nLen = (strSend.GetLength() + 1) * sizeof(TCHAR);
	DWORD dwWrite = 0;
	gSerialPort.WriteFile((TCHAR*)strSend.GetBuffer(), nLen, &dwWrite, &overlappedWrite);

	pEditSend->SetWindowTextW(_T("")); //清空编辑框

	pEditRecv->GetWindowText(strRecv);
	strRecv += _T("Send: ");
	strRecv += strSend;
	strRecv += _T("\r\n");
	pEditRecv->SetWindowText(strRecv);
	
	if (overlappedWrite.hEvent != 0) {
		CloseHandle(overlappedWrite.hEvent);
	}	
	Sleep(100);
}
