
// MFCSerialBasicDlg.h: 头文件
//

#pragma once
#include "SerialPort.h"

// CMFCSerialBasicDlg 对话框
class CMFCSerialBasicDlg : public CDialogEx
{
// 构造
public:
	CMFCSerialBasicDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCSERIALBASIC_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

public:
	void InitComboBox();

// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnOpencomm();
	afx_msg void OnBnClickedBtnSend();
};
