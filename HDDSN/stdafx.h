//stdafx.h：标准系统包含文件的包含文件，
//或项目特定的包括经常使用的文件，
//但很少更换

#pragma once

#ifndef _SECURE_ATL
#define _SECURE_ATL 1
#endif

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN
#endif

#ifndef WINVER
#define WINVER 0x0501
#endif

#ifndef _WIN32_WINNT              
#define _WIN32_WINNT 0x0501
#endif						

#ifndef _WIN32_WINDOWS
#define _WIN32_WINDOWS 0x0410
#endif

#ifndef _WIN32_IE
#define _WIN32_IE 0x0600
#endif

#define _AFX_NO_MFC_CONTROLS_IN_DIALOGS
#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC核心和标准组件
#include <afxext.h>         // 扩展MFC组件

#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>		// MFC IE4 公共控件支持
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC Windows公共控件支持
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxdhtml.h>			// HTML对话框

//#include "DHtmlDialogEx.h"	
//#include "DHtmlMainDialog.h"	

#include <comutil.h>

//#include "CommonFx.h"
#include "UtilityFx.h"


#pragma warning(disable : 4996) //禁止4996警告错误

//------------------------------------------------
// Option Flags
//------------------------------------------------

// For Task Tray Icon Feature
#define OPTION_TASK_TRAY

//------------------------------------------------
// Global Sttings
//------------------------------------------------

// Version Information
#define PROJECT_NAME			_T("HDDInfo")
#define PRODUCT_NAME			_T("HDDInfo")

#define PRODUCT_SHORT_NAME		_T("内核 CDI 8.17.14")

#ifdef _M_ARM
#define PRODUCT_EDITION			_T("ARM32")//定义编译产品版本
#elif _M_ARM64
#define PRODUCT_EDITION			_T("ARM64")
#elif _M_X64
#define PRODUCT_EDITION			_T("x64")
#else
#define PRODUCT_EDITION			_T("x86")

#endif

#define PRODUCT_VERSION				L"8.17.14"
#define PRODUCT_RELEASE				L"2023/02/14"
#define PRODUCT_COPY_YEAR			L"2008-2023"
#define PRODUCT_LICENSE				L"开源许可"

// Command
static const int TRAY_TEMPERATURE_ICON_BASE = WM_APP + 0x1200;
static const int SELECT_DISK_BASE = WM_APP + 0x1300;
static const int AUTO_REFRESH_TARGET_BASE = WM_APP + 0x1400;
static const int SHOW_GRAPH_BASE = WM_APP + 0x1500;
static const int ALARM_SETTING_HEALTH_STATUS_BASE = WM_APP + 0x1900;
static const int ALARM_SETTING_TEMPERATURE_BASE = WM_APP + 0x2000; // Main Only
static const int GRAPH_DISK_INDEX = WM_APP + 0x2000; // Graph Only

static const int RE_EXEC = 5963;