﻿
// HDDSNDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "HDDSN.h"
#include "HDDSNDlg.h"
#include "afxdialogex.h"

#include "AtaSmart.h"
#include <VersionHelpers.h>


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


// CHDDSNDlg 对话框



CHDDSNDlg::CHDDSNDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_HDDSN_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CHDDSNDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CHDDSNDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//ON_BN_CLICKED(IDOK, &CHDDSNDlg::OnBnClickedOk)
	//ON_BN_CLICKED(IDCANCEL, &CHDDSNDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDOSVER, &CHDDSNDlg::OnOsver)
END_MESSAGE_MAP()


// CHDDSNDlg 消息处理程序

BOOL CHDDSNDlg::OnInitDialog()
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

	//ShowWindow(SW_MAXIMIZE);//窗口最大化
	//ShowWindow(SW_MINIMIZE);//窗口最小化
	ShowWindow(SW_RESTORE);

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CHDDSNDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CHDDSNDlg::OnPaint()
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
HCURSOR CHDDSNDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CHDDSNDlg::OnOK() //虚拟确定按钮

{
CAtaSmart m_ATA;
auto flagCD = FALSE;
m_ATA.Init(TRUE, TRUE, &flagCD, TRUE, TRUE, FALSE);

CString strHDDName = m_ATA.vars[0].Model;
CString strHDDSN = m_ATA.vars[0].SerialNumber;

SetDlgItemText(IDC_EDIT1, strHDDName);
SetDlgItemText(IDC_EDIT2, strHDDSN);
}

void CHDDSNDlg::OnOsver()
{
	CAboutDlg dlgAbout;
	dlgAbout.DoModal();
}



//void CHDDSNDlg::OnBnClickedOk()
//{
//	// TODO: 在此添加控件通知处理程序代码
//	CAtaSmart m_ATA;
//	auto flagCD = FALSE;
//	m_ATA.Init(TRUE, TRUE, &flagCD, TRUE, TRUE, FALSE);
//
//	CString strHDDName = m_ATA.vars[0].Model;
//	CString strHDDSN = m_ATA.vars[0].SerialNumber;
//
//	SetDlgItemText(IDC_EDIT1, strHDDName);
//	SetDlgItemText(IDC_EDIT2, strHDDSN);
//
//	//CDialogEx::OnOK();
//}


//void CHDDSNDlg::OnBnClickedCancel()
//{
//	// TODO: 在此添加控件通知处理程序代码
//	CDialogEx::OnCancel();
//}


//void CHDDSNDlg::OnBnClickedOsver()
//{
//	//IDOSVER
//	if (!IsWindows10OrGreater())
//	{
//		MessageBox(_T("You need at least Windows 10."), _T("Version Not Supported"), MB_OK);
//	}
//	else
//	{
//		MessageBox(_T("Windows 10以上版本"), _T("支持"), MB_OK);
//	}
//}
